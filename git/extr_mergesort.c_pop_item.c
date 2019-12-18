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
struct mergesort_sublist {void const* ptr; int len; } ;

/* Variables and functions */

__attribute__((used)) static void *pop_item(struct mergesort_sublist *l,
		      void *(*get_next_fn)(const void *))
{
	void *p = l->ptr;
	l->ptr = get_next_fn(l->ptr);
	l->len = l->ptr ? (l->len - 1) : 0;
	return p;
}