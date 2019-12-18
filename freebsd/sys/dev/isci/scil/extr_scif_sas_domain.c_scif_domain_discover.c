#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; int /*<<< orphan*/  remote_device_list; } ;
struct TYPE_3__ {scalar_t__ (* discover_handler ) (int /*<<< orphan*/ *,int,int) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_DOMAIN_HANDLE_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ SCI_WARNING_TIMER_CONFLICT ; 
 int sci_abstract_list_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int,int) ; 

SCI_STATUS scif_domain_discover(
   SCI_DOMAIN_HANDLE_T   domain,
   U32                   discover_timeout,
   U32                   device_timeout
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T*) domain;
   SCI_STATUS          status    = SCI_SUCCESS;
   SCI_STATUS          op_status = SCI_SUCCESS;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_domain_discover(0x%x, 0x%x, 0x%x) enter\n",
      domain, discover_timeout, device_timeout
   ));

   // Check to make sure the size of the domain doesn't cause potential issues
   // with the remote device timer and the domain timer.
   if ((device_timeout * sci_abstract_list_size(&fw_domain->remote_device_list))
        > discover_timeout)
      status = SCI_WARNING_TIMER_CONFLICT;

   op_status = fw_domain->state_handlers->discover_handler(
                  &fw_domain->parent, discover_timeout, device_timeout
               );

   // The status of the discover operation takes priority.
   if (  (status == SCI_SUCCESS)
      || (status != SCI_SUCCESS && op_status != SCI_SUCCESS) )
   {
      status = op_status;
   }

   return status;
}