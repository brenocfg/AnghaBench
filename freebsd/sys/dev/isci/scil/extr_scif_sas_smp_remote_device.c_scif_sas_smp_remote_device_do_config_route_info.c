#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_9__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_11__ {scalar_t__ attached_device_type; TYPE_1__ attached_sas_address; } ;
struct TYPE_10__ {scalar_t__ high; scalar_t__ low; } ;
typedef  TYPE_2__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_3__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SMP_NO_DEVICE_ATTACHED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_remote_device_get_sas_address (int /*<<< orphan*/ ,TYPE_2__*) ; 

BOOL scif_sas_smp_remote_device_do_config_route_info(
   SCIF_SAS_REMOTE_DEVICE_T * device_being_config,
   SCIF_SAS_SMP_PHY_T       * destination_smp_phy
)
{
   SCI_SAS_ADDRESS_T device_being_config_sas_address;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(device_being_config),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_do_config_route_info(0x%x, 0x%x) enter\n",
      device_being_config, destination_smp_phy
   ));

   scic_remote_device_get_sas_address(
      device_being_config->core_object, &device_being_config_sas_address
   );

   //refer to SAS-2 spec 4.8.3, rule (b)
   if ((destination_smp_phy->attached_sas_address.low == 0
        && destination_smp_phy->attached_sas_address.high == 0)
       && (destination_smp_phy->attached_device_type == SMP_NO_DEVICE_ATTACHED))
   {
      return FALSE;
   }

   //refer to SAS-2 spec 4.8.3, rule (c), self-referencing.
   if (destination_smp_phy->attached_sas_address.high ==
          device_being_config_sas_address.high
       && destination_smp_phy->attached_sas_address.low ==
             device_being_config_sas_address.low)
   {
      return FALSE;
   }

   //There will be no cases that falling into rule (a), (d), (e) to be excluded,
   //based on our current mechanism of cofig route table.

   return TRUE;
}