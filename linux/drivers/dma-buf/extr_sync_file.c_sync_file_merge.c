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
struct sync_file {int /*<<< orphan*/  file; int /*<<< orphan*/  user_name; } ;
struct dma_fence {scalar_t__ context; int /*<<< orphan*/  ops; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 scalar_t__ __dma_fence_is_later (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_fence (struct dma_fence**,int*,struct dma_fence*) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 struct dma_fence** get_fences (struct sync_file*,int*) ; 
 struct dma_fence** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 struct dma_fence** krealloc (struct dma_fence**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct sync_file* sync_file_alloc () ; 
 scalar_t__ sync_file_set_fence (struct sync_file*,struct dma_fence**,int) ; 

__attribute__((used)) static struct sync_file *sync_file_merge(const char *name, struct sync_file *a,
					 struct sync_file *b)
{
	struct sync_file *sync_file;
	struct dma_fence **fences, **nfences, **a_fences, **b_fences;
	int i, i_a, i_b, num_fences, a_num_fences, b_num_fences;

	sync_file = sync_file_alloc();
	if (!sync_file)
		return NULL;

	a_fences = get_fences(a, &a_num_fences);
	b_fences = get_fences(b, &b_num_fences);
	if (a_num_fences > INT_MAX - b_num_fences)
		return NULL;

	num_fences = a_num_fences + b_num_fences;

	fences = kcalloc(num_fences, sizeof(*fences), GFP_KERNEL);
	if (!fences)
		goto err;

	/*
	 * Assume sync_file a and b are both ordered and have no
	 * duplicates with the same context.
	 *
	 * If a sync_file can only be created with sync_file_merge
	 * and sync_file_create, this is a reasonable assumption.
	 */
	for (i = i_a = i_b = 0; i_a < a_num_fences && i_b < b_num_fences; ) {
		struct dma_fence *pt_a = a_fences[i_a];
		struct dma_fence *pt_b = b_fences[i_b];

		if (pt_a->context < pt_b->context) {
			add_fence(fences, &i, pt_a);

			i_a++;
		} else if (pt_a->context > pt_b->context) {
			add_fence(fences, &i, pt_b);

			i_b++;
		} else {
			if (__dma_fence_is_later(pt_a->seqno, pt_b->seqno,
						 pt_a->ops))
				add_fence(fences, &i, pt_a);
			else
				add_fence(fences, &i, pt_b);

			i_a++;
			i_b++;
		}
	}

	for (; i_a < a_num_fences; i_a++)
		add_fence(fences, &i, a_fences[i_a]);

	for (; i_b < b_num_fences; i_b++)
		add_fence(fences, &i, b_fences[i_b]);

	if (i == 0)
		fences[i++] = dma_fence_get(a_fences[0]);

	if (num_fences > i) {
		nfences = krealloc(fences, i * sizeof(*fences),
				  GFP_KERNEL);
		if (!nfences)
			goto err;

		fences = nfences;
	}

	if (sync_file_set_fence(sync_file, fences, i) < 0) {
		kfree(fences);
		goto err;
	}

	strlcpy(sync_file->user_name, name, sizeof(sync_file->user_name));
	return sync_file;

err:
	fput(sync_file->file);
	return NULL;

}