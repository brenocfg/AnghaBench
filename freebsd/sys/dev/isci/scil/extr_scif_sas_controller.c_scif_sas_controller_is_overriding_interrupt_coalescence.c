#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_9__ {TYPE_3__* domains; } ;
struct TYPE_6__ {scalar_t__ current_state_id; } ;
struct TYPE_7__ {TYPE_1__ state_machine; } ;
struct TYPE_8__ {TYPE_2__ parent; } ;
typedef  TYPE_4__ SCIF_SAS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCI_BASE_DOMAIN_STATE_DISCOVERING ; 
 size_t SCI_MAX_DOMAINS ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL scif_sas_controller_is_overriding_interrupt_coalescence(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   U8 index;

   for(index = 0; index < SCI_MAX_DOMAINS; index++)
   {
      if(fw_controller->domains[index].parent.state_machine.current_state_id ==
            SCI_BASE_DOMAIN_STATE_DISCOVERING)
         return TRUE;
   }

   return FALSE;
}