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
typedef  int /*<<< orphan*/  (* SCI_START_INTERNAL_IO_ROUTINE ) (void*) ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  FUNCPTR ;

/* Variables and functions */

void
scif_cb_start_internal_io_task_schedule(SCI_CONTROLLER_HANDLE_T scif_controller,
    FUNCPTR start_internal_io_task_routine, void *context)
{
	/** @todo Use FreeBSD tasklet to defer this routine to a later time,
	 *  rather than calling the routine inline.
	 */
	SCI_START_INTERNAL_IO_ROUTINE sci_start_internal_io_routine =
	    (SCI_START_INTERNAL_IO_ROUTINE)start_internal_io_task_routine;

	sci_start_internal_io_routine(context);
}