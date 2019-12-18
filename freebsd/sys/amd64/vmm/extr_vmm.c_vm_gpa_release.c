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
typedef  void* vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_ACTIVE ; 
 int /*<<< orphan*/  vm_page_unwire (void*,int /*<<< orphan*/ ) ; 

void
vm_gpa_release(void *cookie)
{
	vm_page_t m = cookie;

	vm_page_unwire(m, PQ_ACTIVE);
}