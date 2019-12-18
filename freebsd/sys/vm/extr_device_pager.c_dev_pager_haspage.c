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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
dev_pager_haspage(vm_object_t object, vm_pindex_t pindex, int *before,
    int *after)
{

	if (before != NULL)
		*before = 0;
	if (after != NULL)
		*after = 0;
	return (TRUE);
}