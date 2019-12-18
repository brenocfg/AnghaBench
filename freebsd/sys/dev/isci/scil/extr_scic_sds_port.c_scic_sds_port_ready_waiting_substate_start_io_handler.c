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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_ready_waiting_substate_start_io_handler(
   SCIC_SDS_PORT_T          *port,
   SCIC_SDS_REMOTE_DEVICE_T *device,
   SCIC_SDS_REQUEST_T       *io_request
)
{
   return SCI_FAILURE_INVALID_STATE;
}