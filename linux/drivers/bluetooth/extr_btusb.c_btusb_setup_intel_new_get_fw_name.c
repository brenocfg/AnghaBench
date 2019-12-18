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
struct intel_version {int hw_variant; int hw_revision; int fw_revision; } ;
struct intel_boot_params {int dev_revid; } ;

/* Variables and functions */
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,...) ; 

__attribute__((used)) static bool btusb_setup_intel_new_get_fw_name(struct intel_version *ver,
					     struct intel_boot_params *params,
					     char *fw_name, size_t len,
					     const char *suffix)
{
	switch (ver->hw_variant) {
	case 0x0b:	/* SfP */
	case 0x0c:	/* WsP */
		snprintf(fw_name, len, "intel/ibt-%u-%u.%s",
			le16_to_cpu(ver->hw_variant),
			le16_to_cpu(params->dev_revid),
			suffix);
		break;
	case 0x11:	/* JfP */
	case 0x12:	/* ThP */
	case 0x13:	/* HrP */
	case 0x14:	/* CcP */
		snprintf(fw_name, len, "intel/ibt-%u-%u-%u.%s",
			le16_to_cpu(ver->hw_variant),
			le16_to_cpu(ver->hw_revision),
			le16_to_cpu(ver->fw_revision),
			suffix);
		break;
	default:
		return false;
	}
	return true;
}