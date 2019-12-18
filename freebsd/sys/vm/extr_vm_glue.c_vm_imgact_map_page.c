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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct sf_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFB_CPUPRIVATE ; 
 int /*<<< orphan*/  sched_pin () ; 
 struct sf_buf* sf_buf_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_imgact_hold_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sf_buf *
vm_imgact_map_page(vm_object_t object, vm_ooffset_t offset)
{
	vm_page_t m;

	m = vm_imgact_hold_page(object, offset);
	if (m == NULL)
		return (NULL);
	sched_pin();
	return (sf_buf_alloc(m, SFB_CPUPRIVATE));
}