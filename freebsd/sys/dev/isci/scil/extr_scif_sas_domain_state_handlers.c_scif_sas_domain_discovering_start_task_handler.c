#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  domain; } ;
struct TYPE_6__ {int /*<<< orphan*/  state_machine; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCI_BASE_DOMAIN_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 scalar_t__ SCI_SAS_HARD_RESET ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_cancel_smp_activities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_domain_ready_start_task_handler (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_task_request_get_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_discovering_start_task_handler(
   SCI_BASE_DOMAIN_T        * domain,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * task_request
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SCIF_SAS_TASK_REQUEST_T  * fw_task = (SCIF_SAS_TASK_REQUEST_T*)task_request;

   //Only let target reset go through.
   if (scif_sas_task_request_get_function(fw_task)
             == SCI_SAS_HARD_RESET)
   {
      //If the domain is in the middle of smp DISCOVER process,
      //interrupt it. After target reset is done, resume the smp DISCOVERY.
      scif_sas_domain_cancel_smp_activities(fw_device->domain);

      return scif_sas_domain_ready_start_task_handler(domain, remote_device, task_request);
   }
   else{
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(domain),
         SCIF_LOG_OBJECT_DOMAIN,
         "Domain:0x%x Device:0x%x State:0x%x start task message invalid\n",
         domain, remote_device,
         sci_base_state_machine_get_state(&domain->state_machine)
      ));

      return SCI_FAILURE_INVALID_STATE;
   }
}