#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int internal_request_entries; int /*<<< orphan*/ * mdes; } ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 size_t SCIF_SAS_MDE_INTERNAL_IO ; 
 int /*<<< orphan*/  SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS ; 
 int /*<<< orphan*/  sci_base_mde_construct (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int scif_sas_internal_request_get_object_size () ; 

void scif_sas_controller_build_mdl(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   // one internal request for each domain.
   sci_base_mde_construct(
      &fw_controller->mdes[SCIF_SAS_MDE_INTERNAL_IO],
      4,
      fw_controller->internal_request_entries *
         scif_sas_internal_request_get_object_size(),
      SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
   );
}