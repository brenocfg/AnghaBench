#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_2__ {int /*<<< orphan*/ * domains; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/ * SCI_DOMAIN_HANDLE_T ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PORT ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scif_controller_get_domain_handle(
   SCI_CONTROLLER_HANDLE_T   controller,
   U8                        port_index,
   SCI_DOMAIN_HANDLE_T     * domain_handle
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T*) controller;

   // Validate the user supplied parameters.
   if (controller == SCI_INVALID_HANDLE)
      return SCI_FAILURE_INVALID_PARAMETER_VALUE;

   // Retrieve the domain handle if the supplied index is legitimate.
   if (port_index < SCI_MAX_PORTS)
   {
      *domain_handle = &fw_controller->domains[port_index];
      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INVALID_PORT;
}