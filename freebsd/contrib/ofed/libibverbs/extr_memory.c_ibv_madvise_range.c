#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ibv_mem_node {uintptr_t start; uintptr_t end; int refcnt; } ;

/* Variables and functions */
 int MADV_DOFORK ; 
 int MADV_DONTFORK ; 
 struct ibv_mem_node* __mm_next (struct ibv_mem_node*) ; 
 struct ibv_mem_node* __mm_prev (struct ibv_mem_node*) ; 
 unsigned long get_page_size (void*) ; 
 struct ibv_mem_node* get_start_node (uintptr_t,uintptr_t,int) ; 
 scalar_t__ huge_page_enabled ; 
 int madvise (void*,uintptr_t,int) ; 
 struct ibv_mem_node* merge_ranges (struct ibv_mem_node*,struct ibv_mem_node*) ; 
 int /*<<< orphan*/  mm_mutex ; 
 unsigned long page_size ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_range (struct ibv_mem_node*,uintptr_t) ; 
 struct ibv_mem_node* undo_node (struct ibv_mem_node*,uintptr_t,int) ; 

__attribute__((used)) static int ibv_madvise_range(void *base, size_t size, int advice)
{
	uintptr_t start, end;
	struct ibv_mem_node *node, *tmp;
	int inc;
	int rolling_back = 0;
	int ret = 0;
	unsigned long range_page_size;

	if (!size)
		return 0;

	if (huge_page_enabled)
		range_page_size = get_page_size(base);
	else
		range_page_size = page_size;

	start = (uintptr_t) base & ~(range_page_size - 1);
	end   = ((uintptr_t) (base + size + range_page_size - 1) &
		 ~(range_page_size - 1)) - 1;

	pthread_mutex_lock(&mm_mutex);
again:
	inc = advice == MADV_DONTFORK ? 1 : -1;

	node = get_start_node(start, end, inc);
	if (!node) {
		ret = -1;
		goto out;
	}

	while (node && node->start <= end) {
		if (node->end > end) {
			if (!split_range(node, end + 1)) {
				ret = -1;
				goto out;
			}
		}

		if ((inc == -1 && node->refcnt == 1) ||
		    (inc ==  1 && node->refcnt == 0)) {
			/*
			 * If this is the first time through the loop,
			 * and we merged this node with the previous
			 * one, then we only want to do the madvise()
			 * on start ... node->end (rather than
			 * starting at node->start).
			 *
			 * Otherwise we end up doing madvise() on
			 * bigger region than we're being asked to,
			 * and that may lead to a spurious failure.
			 */
			if (start > node->start)
				ret = madvise((void *) start, node->end - start + 1,
					      advice);
			else
				ret = madvise((void *) node->start,
					      node->end - node->start + 1,
					      advice);
			if (ret) {
				node = undo_node(node, start, inc);

				if (rolling_back || !node)
					goto out;

				/* madvise failed, roll back previous changes */
				rolling_back = 1;
				advice = advice == MADV_DONTFORK ?
					MADV_DOFORK : MADV_DONTFORK;
				tmp = __mm_prev(node);
				if (!tmp || start > tmp->end)
					goto out;
				end = tmp->end;
				goto again;
			}
		}

		node->refcnt += inc;
		node = __mm_next(node);
	}

	if (node) {
		tmp = __mm_prev(node);
		if (tmp && node->refcnt == tmp->refcnt)
			node = merge_ranges(node, tmp);
	}

out:
	if (rolling_back)
		ret = -1;

	pthread_mutex_unlock(&mm_mutex);

	return ret;
}