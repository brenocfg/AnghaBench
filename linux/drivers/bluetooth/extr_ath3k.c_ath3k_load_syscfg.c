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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct ath3k_version {int ref_clock; int /*<<< orphan*/  rom_version; } ;

/* Variables and functions */
 int ATH3K_NAME_LEN ; 
#define  ATH3K_XTAL_FREQ_19P2 130 
#define  ATH3K_XTAL_FREQ_26M 129 
#define  ATH3K_XTAL_FREQ_40M 128 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int EBUSY ; 
 int ath3k_get_state (struct usb_device*,unsigned char*) ; 
 int ath3k_get_version (struct usb_device*,struct ath3k_version*) ; 
 int ath3k_load_fwfile (struct usb_device*,struct firmware const*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char*) ; 

__attribute__((used)) static int ath3k_load_syscfg(struct usb_device *udev)
{
	unsigned char fw_state;
	char filename[ATH3K_NAME_LEN];
	const struct firmware *firmware;
	struct ath3k_version fw_version;
	int clk_value, ret;

	ret = ath3k_get_state(udev, &fw_state);
	if (ret < 0) {
		BT_ERR("Can't get state to change to load configuration err");
		return -EBUSY;
	}

	ret = ath3k_get_version(udev, &fw_version);
	if (ret < 0) {
		BT_ERR("Can't get version to change to load ram patch err");
		return ret;
	}

	switch (fw_version.ref_clock) {

	case ATH3K_XTAL_FREQ_26M:
		clk_value = 26;
		break;
	case ATH3K_XTAL_FREQ_40M:
		clk_value = 40;
		break;
	case ATH3K_XTAL_FREQ_19P2:
		clk_value = 19;
		break;
	default:
		clk_value = 0;
		break;
	}

	snprintf(filename, ATH3K_NAME_LEN, "ar3k/ramps_0x%08x_%d%s",
		le32_to_cpu(fw_version.rom_version), clk_value, ".dfu");

	ret = request_firmware(&firmware, filename, &udev->dev);
	if (ret < 0) {
		BT_ERR("Configuration file not found %s", filename);
		return ret;
	}

	ret = ath3k_load_fwfile(udev, firmware);
	release_firmware(firmware);

	return ret;
}