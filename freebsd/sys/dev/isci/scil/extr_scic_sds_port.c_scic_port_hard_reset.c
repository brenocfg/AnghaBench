#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_7__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_PORT_HANDLE_T ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_port_hard_reset(
   SCI_PORT_HANDLE_T handle,
   U32               reset_timeout
)
{
   SCIC_SDS_PORT_T * this_port = (SCIC_SDS_PORT_T *)handle;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "scic_port_hard_reset(0x%x, 0x%x) enter\n",
      handle, reset_timeout
   ));

   return this_port->state_handlers->parent.reset_handler(
                                       &this_port->parent,
                                       reset_timeout
                                     );
}