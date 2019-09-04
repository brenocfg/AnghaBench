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
struct mergesort_sublist {void const* ptr; unsigned long len; } ;

/* Variables and functions */
 void* get_nth_next (void const*,unsigned long,void* (*) (void const*)) ; 
 void* pop_item (struct mergesort_sublist*,void* (*) (void const*)) ; 

void *llist_mergesort(void *list,
		      void *(*get_next_fn)(const void *),
		      void (*set_next_fn)(void *, void *),
		      int (*compare_fn)(const void *, const void *))
{
	unsigned long l;

	if (!list)
		return NULL;
	for (l = 1; ; l *= 2) {
		void *curr;
		struct mergesort_sublist p, q;

		p.ptr = list;
		q.ptr = get_nth_next(p.ptr, l, get_next_fn);
		if (!q.ptr)
			break;
		p.len = q.len = l;

		if (compare_fn(p.ptr, q.ptr) > 0)
			list = curr = pop_item(&q, get_next_fn);
		else
			list = curr = pop_item(&p, get_next_fn);

		while (p.ptr) {
			while (p.len || q.len) {
				void *prev = curr;

				if (!p.len)
					curr = pop_item(&q, get_next_fn);
				else if (!q.len)
					curr = pop_item(&p, get_next_fn);
				else if (compare_fn(p.ptr, q.ptr) > 0)
					curr = pop_item(&q, get_next_fn);
				else
					curr = pop_item(&p, get_next_fn);
				set_next_fn(prev, curr);
			}
			p.ptr = q.ptr;
			p.len = l;
			q.ptr = get_nth_next(p.ptr, l, get_next_fn);
			q.len = q.ptr ? l : 0;

		}
		set_next_fn(curr, NULL);
	}
	return list;
}