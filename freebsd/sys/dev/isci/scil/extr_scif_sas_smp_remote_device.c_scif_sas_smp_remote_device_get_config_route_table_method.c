#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_CONFIG_ROUTE_TABLE_ALL_PHYS ; 

U8 scif_sas_smp_remote_device_get_config_route_table_method(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   U8 config_route_table_method;

   //config_route_table_method = SCIF_SAS_CONFIG_ROUTE_TABLE_MIDDLE_PHY_ONLY;
   config_route_table_method = SCIF_SAS_CONFIG_ROUTE_TABLE_ALL_PHYS;

   return config_route_table_method;
}