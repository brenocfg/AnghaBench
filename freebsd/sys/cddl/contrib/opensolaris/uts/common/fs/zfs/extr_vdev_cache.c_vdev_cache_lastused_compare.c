#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ve_lastused; } ;
typedef  TYPE_1__ vdev_cache_entry_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int vdev_cache_offset_compare (void const*,void const*) ; 

__attribute__((used)) static int
vdev_cache_lastused_compare(const void *a1, const void *a2)
{
	const vdev_cache_entry_t *ve1 = (const vdev_cache_entry_t *)a1;
	const vdev_cache_entry_t *ve2 = (const vdev_cache_entry_t *)a2;

	int cmp = AVL_CMP(ve1->ve_lastused, ve2->ve_lastused);
	if (likely(cmp))
		return (cmp);

	/*
	 * Among equally old entries, sort by offset to ensure uniqueness.
	 */
	return (vdev_cache_offset_compare(a1, a2));
}