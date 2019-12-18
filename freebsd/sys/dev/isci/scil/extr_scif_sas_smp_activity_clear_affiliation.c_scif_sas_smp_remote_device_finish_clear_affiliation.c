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
struct TYPE_4__ {int /*<<< orphan*/ * domain; } ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_sas_domain_continue_clear_affiliation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_clear (TYPE_1__*) ; 

void scif_sas_smp_remote_device_finish_clear_affiliation(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = fw_device->domain;

   scif_sas_smp_remote_device_clear(fw_device);

   //let domain continue to clear affiliation on other smp devices.
   scif_sas_domain_continue_clear_affiliation(fw_domain);
}