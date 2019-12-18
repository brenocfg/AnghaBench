#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ error; } ;
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCI_CONTROLLER_FATAL_MEMORY_ERROR ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ scic_sds_abort_reqests (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_terminate_reqests(
        SCIC_SDS_CONTROLLER_T *this_controller,
        SCIC_SDS_REMOTE_DEVICE_T *this_remote_device,
        SCIC_SDS_PORT_T *this_port
)
{
    SCI_STATUS status = SCI_SUCCESS;
    SCI_STATUS abort_status = SCI_SUCCESS;

    // move all request to abort state
    abort_status = scic_sds_abort_reqests(this_controller, this_remote_device, this_port);

    if (abort_status != SCI_SUCCESS)
        status = abort_status;

    //move all request to complete state
    if (this_controller->parent.error == SCI_CONTROLLER_FATAL_MEMORY_ERROR)
        abort_status = scic_sds_abort_reqests(this_controller, this_remote_device, this_port);

    if (abort_status != SCI_SUCCESS)
        status = abort_status;

    return status;
}