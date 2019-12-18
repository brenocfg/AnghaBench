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
struct TYPE_5__ {int max_ncq_depth; void* ignore_fua; void* clear_affiliation_during_controller_stop; int /*<<< orphan*/  reset_type; void* is_non_zero_buffer_offsets_enabled; void* is_sata_standby_timer_enabled; void* is_sata_ncq_enabled; } ;
struct TYPE_6__ {TYPE_1__ sas; } ;
struct TYPE_7__ {TYPE_2__ user_parameters; } ;
typedef  TYPE_2__ SCIF_USER_PARAMETERS_T ;
typedef  TYPE_3__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SCI_SAS_LOGICAL_UNIT_RESET ; 
 void* TRUE ; 

void scif_sas_controller_set_default_config_parameters(
   SCIF_SAS_CONTROLLER_T * this_controller
)
{
   SCIF_USER_PARAMETERS_T * scif_parms = &(this_controller->user_parameters);

   scif_parms->sas.is_sata_ncq_enabled = TRUE;
   scif_parms->sas.max_ncq_depth = 32;
   scif_parms->sas.is_sata_standby_timer_enabled = FALSE;
   scif_parms->sas.is_non_zero_buffer_offsets_enabled = FALSE;
   scif_parms->sas.reset_type = SCI_SAS_LOGICAL_UNIT_RESET;
   scif_parms->sas.clear_affiliation_during_controller_stop = TRUE;
   scif_parms->sas.ignore_fua = FALSE;

}