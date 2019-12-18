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

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  xen_intr_handle_upcall (void*) ; 

__attribute__((used)) static int
xenpci_intr_filter(void *trap_frame)
{
	xen_intr_handle_upcall(trap_frame);
	return (FILTER_HANDLED);
}