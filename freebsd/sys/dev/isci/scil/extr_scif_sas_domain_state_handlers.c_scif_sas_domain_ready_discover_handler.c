#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* U32 ;
struct TYPE_4__ {int /*<<< orphan*/  status; void* timeout; int /*<<< orphan*/  timer; void* device_timeout; } ;
struct TYPE_5__ {TYPE_1__ operation; int /*<<< orphan*/  controller; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_DOMAIN_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scif_sas_domain_transition_to_discovering_state (TYPE_2__*) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_ready_discover_handler(
   SCI_BASE_DOMAIN_T * domain,
   U32                 op_timeout,
   U32                 device_timeout
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T *)domain;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_ready_discover_handler(0x%x, 0x%x, 0x%x) enter\n",
      domain, op_timeout, device_timeout
   ));

   fw_domain->operation.timeout        = op_timeout;
   fw_domain->operation.device_timeout = device_timeout;
   fw_domain->operation.status         = SCI_SUCCESS;

   scif_cb_timer_start(
      fw_domain->controller,
      fw_domain->operation.timer,
      fw_domain->operation.timeout
   );

   scif_sas_domain_transition_to_discovering_state(fw_domain);

   return fw_domain->operation.status;
}