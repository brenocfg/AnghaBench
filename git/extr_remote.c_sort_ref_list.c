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
struct ref {int dummy; } ;

/* Variables and functions */
 struct ref* llist_mergesort (struct ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  ref_list_get_next ; 
 int /*<<< orphan*/  ref_list_set_next ; 

void sort_ref_list(struct ref **l, int (*cmp)(const void *, const void *))
{
	*l = llist_mergesort(*l, ref_list_get_next, ref_list_set_next, cmp);
}