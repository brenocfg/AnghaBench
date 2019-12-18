#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCI_BASE_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_default_start_io_handler(
   SCI_BASE_DOMAIN_T        * domain,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request
)
{
   SCIF_LOG_WARNING((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "Domain:0x%x Device:0x%x State:0x%x start IO message invalid\n",
      domain, remote_device,
      sci_base_state_machine_get_state(&domain->state_machine)
   ));

   return SCI_FAILURE_INVALID_STATE;
}