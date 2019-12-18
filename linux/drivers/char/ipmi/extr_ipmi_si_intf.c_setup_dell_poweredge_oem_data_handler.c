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
struct ipmi_device_id {scalar_t__ manufacturer_id; scalar_t__ device_id; scalar_t__ device_revision; scalar_t__ ipmi_version; } ;
struct smi_info {void* oem_data_avail_handler; struct ipmi_device_id device_id; } ;

/* Variables and functions */
 scalar_t__ DELL_IANA_MFR_ID ; 
 scalar_t__ DELL_POWEREDGE_8G_BMC_DEVICE_ID ; 
 scalar_t__ DELL_POWEREDGE_8G_BMC_DEVICE_REV ; 
 scalar_t__ DELL_POWEREDGE_8G_BMC_IPMI_VERSION ; 
 int ipmi_version_major (struct ipmi_device_id*) ; 
 int ipmi_version_minor (struct ipmi_device_id*) ; 
 void* oem_data_avail_to_receive_msg_avail ; 

__attribute__((used)) static void setup_dell_poweredge_oem_data_handler(struct smi_info *smi_info)
{
	struct ipmi_device_id *id = &smi_info->device_id;
	if (id->manufacturer_id == DELL_IANA_MFR_ID) {
		if (id->device_id       == DELL_POWEREDGE_8G_BMC_DEVICE_ID  &&
		    id->device_revision == DELL_POWEREDGE_8G_BMC_DEVICE_REV &&
		    id->ipmi_version   == DELL_POWEREDGE_8G_BMC_IPMI_VERSION) {
			smi_info->oem_data_avail_handler =
				oem_data_avail_to_receive_msg_avail;
		} else if (ipmi_version_major(id) < 1 ||
			   (ipmi_version_major(id) == 1 &&
			    ipmi_version_minor(id) < 5)) {
			smi_info->oem_data_avail_handler =
				oem_data_avail_to_receive_msg_avail;
		}
	}
}