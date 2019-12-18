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
typedef  int /*<<< orphan*/  SMP_RESPONSE_REPORT_PHY_SATA_T ;

/* Variables and functions */

void scif_sas_remote_device_save_report_phy_sata_information(
   SMP_RESPONSE_REPORT_PHY_SATA_T * report_phy_sata_response
)
{
   //do nothing currently. Later, if needed, we will search the existed
   //remote device by stp_sas_address, then save more information for
   //that device off the report_phy_sata_response. This assumes the
   //stp_sas_address from report_phy_sata response is the same sas address
   //from discover response.

   return;
}