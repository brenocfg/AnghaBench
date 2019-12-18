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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 size_t SCIF_SAS_MDE_INTERNAL_IO ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD ; 
 int /*<<< orphan*/  SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ sci_base_mde_is_valid (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int scif_sas_internal_request_get_object_size () ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_validate_mdl(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   BOOL is_mde_list_valid;

   // Currently there is only a single MDE in the list.
   is_mde_list_valid = sci_base_mde_is_valid(
                          &fw_controller->mdes[SCIF_SAS_MDE_INTERNAL_IO],
                          4,
                          fw_controller->internal_request_entries *
                             scif_sas_internal_request_get_object_size(),
                          SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
                       );

   if (is_mde_list_valid == FALSE)
      return SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD;

   return SCI_SUCCESS;
}