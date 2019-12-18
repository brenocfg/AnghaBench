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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u8 ;
typedef  int u32 ;
struct rome_config {int /*<<< orphan*/  fwname; int /*<<< orphan*/  type; int /*<<< orphan*/  user_baud_rate; } ;
struct hci_dev {int dummy; } ;
typedef  enum qca_btsoc_type { ____Placeholder_qca_btsoc_type } qca_btsoc_type ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_TYPE_NVM ; 
 int /*<<< orphan*/  TLV_TYPE_PATCH ; 
 int /*<<< orphan*/  bt_dev_dbg (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int qca_download_firmware (struct hci_dev*,struct rome_config*) ; 
 scalar_t__ qca_is_wcn399x (int) ; 
 int qca_send_reset (struct hci_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

int qca_uart_setup(struct hci_dev *hdev, uint8_t baudrate,
		   enum qca_btsoc_type soc_type, u32 soc_ver,
		   const char *firmware_name)
{
	struct rome_config config;
	int err;
	u8 rom_ver = 0;

	bt_dev_dbg(hdev, "QCA setup on UART");

	config.user_baud_rate = baudrate;

	/* Download rampatch file */
	config.type = TLV_TYPE_PATCH;
	if (qca_is_wcn399x(soc_type)) {
		/* Firmware files to download are based on ROM version.
		 * ROM version is derived from last two bytes of soc_ver.
		 */
		rom_ver = ((soc_ver & 0x00000f00) >> 0x04) |
			    (soc_ver & 0x0000000f);
		snprintf(config.fwname, sizeof(config.fwname),
			 "qca/crbtfw%02x.tlv", rom_ver);
	} else {
		snprintf(config.fwname, sizeof(config.fwname),
			 "qca/rampatch_%08x.bin", soc_ver);
	}

	err = qca_download_firmware(hdev, &config);
	if (err < 0) {
		bt_dev_err(hdev, "QCA Failed to download patch (%d)", err);
		return err;
	}

	/* Give the controller some time to get ready to receive the NVM */
	msleep(10);

	/* Download NVM configuration */
	config.type = TLV_TYPE_NVM;
	if (firmware_name)
		snprintf(config.fwname, sizeof(config.fwname),
			 "qca/%s", firmware_name);
	else if (qca_is_wcn399x(soc_type))
		snprintf(config.fwname, sizeof(config.fwname),
			 "qca/crnv%02x.bin", rom_ver);
	else
		snprintf(config.fwname, sizeof(config.fwname),
			 "qca/nvm_%08x.bin", soc_ver);

	err = qca_download_firmware(hdev, &config);
	if (err < 0) {
		bt_dev_err(hdev, "QCA Failed to download NVM (%d)", err);
		return err;
	}

	/* Perform HCI reset */
	err = qca_send_reset(hdev);
	if (err < 0) {
		bt_dev_err(hdev, "QCA Failed to run HCI_RESET (%d)", err);
		return err;
	}

	bt_dev_info(hdev, "QCA setup on UART is completed");

	return 0;
}