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
struct TYPE_6__ {TYPE_1__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* complete_io_handler ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_port_complete_io(
   SCIC_SDS_PORT_T          *this_port,
   SCIC_SDS_REMOTE_DEVICE_T *the_device,
   SCIC_SDS_REQUEST_T       *the_io_request
)
{
   return this_port->state_handlers->complete_io_handler(
                                       this_port, the_device, the_io_request);
}