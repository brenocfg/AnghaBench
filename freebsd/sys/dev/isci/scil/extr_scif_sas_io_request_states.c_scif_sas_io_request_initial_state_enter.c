#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {TYPE_1__ parent; } ;
struct TYPE_5__ {TYPE_3__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_INITIAL ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_io_request_state_handler_table ; 

__attribute__((used)) static
void scif_sas_io_request_initial_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T *)object;

   SET_STATE_HANDLER(
      &fw_io->parent,
      scif_sas_io_request_state_handler_table,
      SCI_BASE_REQUEST_STATE_INITIAL
   );

   // Initial state is a transitional state to the constructed state
   sci_base_state_machine_change_state(
      &fw_io->parent.parent.state_machine, SCI_BASE_REQUEST_STATE_CONSTRUCTED
   );
}