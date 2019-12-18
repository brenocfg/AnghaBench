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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SAS_HARD_RESET ; 

uint8_t scif_cb_task_request_get_function(void * scif_user_task_request)
{
	/* SCIL supports many types of task management functions, but this
	 *  driver only uses HARD_RESET.
	 */
	return (SCI_SAS_HARD_RESET);
}