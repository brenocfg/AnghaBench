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
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_ERROR ;

/* Variables and functions */
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

void scif_cb_controller_error(SCI_CONTROLLER_HANDLE_T controller,
    SCI_CONTROLLER_ERROR error)
{

	isci_log_message(0, "ISCI", "scif_cb_controller_error: 0x%x\n",
	    error);
}