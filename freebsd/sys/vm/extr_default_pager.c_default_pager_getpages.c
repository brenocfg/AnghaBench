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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int VM_PAGER_FAIL ; 

__attribute__((used)) static int
default_pager_getpages(vm_object_t object, vm_page_t *m, int count,
    int *rbehind, int *rahead)
{

	/*
	 * Since an OBJT_DEFAULT object is converted to OBJT_SWAP by the first
	 * call to the putpages method, this function will never be called on
	 * a vm_page with assigned swap.
	 */
	return (VM_PAGER_FAIL);
}