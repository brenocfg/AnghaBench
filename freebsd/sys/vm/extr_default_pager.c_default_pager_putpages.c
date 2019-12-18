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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pgo_putpages ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 TYPE_1__ swappagerops ; 

__attribute__((used)) static void
default_pager_putpages(vm_object_t object, vm_page_t *m, int count,
    int flags, int *rtvals)
{

	/* The swap pager will convert the object to OBJT_SWAP. */
	swappagerops.pgo_putpages(object, m, count, flags, rtvals);
}