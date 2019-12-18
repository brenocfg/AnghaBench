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
struct qca_data {int /*<<< orphan*/  flags; } ;
struct hci_uart {struct hci_dev* hdev; struct qca_data* priv; } ;
struct hci_dev {int /*<<< orphan*/  set_bdaddr; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  quirks; } ;
typedef  enum qca_btsoc_type { ____Placeholder_qca_btsoc_type } qca_btsoc_type ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  HCI_QUIRK_NON_PERSISTENT_SETUP ; 
 int /*<<< orphan*/  HCI_QUIRK_SIMULTANEOUS_DISCOVERY ; 
 int /*<<< orphan*/  HCI_QUIRK_USE_BDADDR_PROPERTY ; 
 unsigned int QCA_BAUDRATE_115200 ; 
 int /*<<< orphan*/  QCA_IBS_ENABLED ; 
 int /*<<< orphan*/  QCA_INIT_SPEED ; 
 int /*<<< orphan*/  QCA_OPER_SPEED ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qca_check_speeds (struct hci_uart*) ; 
 int /*<<< orphan*/  qca_debugfs_init (struct hci_dev*) ; 
 unsigned int qca_get_baudrate_value (unsigned int) ; 
 char* qca_get_firmware_name (struct hci_uart*) ; 
 unsigned int qca_get_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 scalar_t__ qca_is_wcn399x (int) ; 
 int /*<<< orphan*/  qca_power_off ; 
 int qca_read_soc_version (struct hci_dev*,int*) ; 
 int /*<<< orphan*/  qca_set_bdaddr ; 
 int /*<<< orphan*/  qca_set_bdaddr_rome ; 
 int qca_set_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int qca_soc_type (struct hci_uart*) ; 
 int qca_uart_setup (struct hci_dev*,unsigned int,int,int,char const*) ; 
 int qca_wcn3990_init (struct hci_uart*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_setup(struct hci_uart *hu)
{
	struct hci_dev *hdev = hu->hdev;
	struct qca_data *qca = hu->priv;
	unsigned int speed, qca_baudrate = QCA_BAUDRATE_115200;
	enum qca_btsoc_type soc_type = qca_soc_type(hu);
	const char *firmware_name = qca_get_firmware_name(hu);
	int ret;
	int soc_ver = 0;

	ret = qca_check_speeds(hu);
	if (ret)
		return ret;

	/* Patch downloading has to be done without IBS mode */
	clear_bit(QCA_IBS_ENABLED, &qca->flags);

	/* Enable controller to do both LE scan and BR/EDR inquiry
	 * simultaneously.
	 */
	set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

	if (qca_is_wcn399x(soc_type)) {
		bt_dev_info(hdev, "setting up wcn3990");

		/* Enable NON_PERSISTENT_SETUP QUIRK to ensure to execute
		 * setup for every hci up.
		 */
		set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);
		set_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks);
		hu->hdev->shutdown = qca_power_off;
		ret = qca_wcn3990_init(hu);
		if (ret)
			return ret;

		ret = qca_read_soc_version(hdev, &soc_ver);
		if (ret)
			return ret;
	} else {
		bt_dev_info(hdev, "ROME setup");
		qca_set_speed(hu, QCA_INIT_SPEED);
	}

	/* Setup user speed if needed */
	speed = qca_get_speed(hu, QCA_OPER_SPEED);
	if (speed) {
		ret = qca_set_speed(hu, QCA_OPER_SPEED);
		if (ret)
			return ret;

		qca_baudrate = qca_get_baudrate_value(speed);
	}

	if (!qca_is_wcn399x(soc_type)) {
		/* Get QCA version information */
		ret = qca_read_soc_version(hdev, &soc_ver);
		if (ret)
			return ret;
	}

	bt_dev_info(hdev, "QCA controller version 0x%08x", soc_ver);
	/* Setup patch / NVM configurations */
	ret = qca_uart_setup(hdev, qca_baudrate, soc_type, soc_ver,
			firmware_name);
	if (!ret) {
		set_bit(QCA_IBS_ENABLED, &qca->flags);
		qca_debugfs_init(hdev);
	} else if (ret == -ENOENT) {
		/* No patch/nvm-config found, run with original fw/config */
		ret = 0;
	} else if (ret == -EAGAIN) {
		/*
		 * Userspace firmware loader will return -EAGAIN in case no
		 * patch/nvm-config is found, so run with original fw/config.
		 */
		ret = 0;
	}

	/* Setup bdaddr */
	if (qca_is_wcn399x(soc_type))
		hu->hdev->set_bdaddr = qca_set_bdaddr;
	else
		hu->hdev->set_bdaddr = qca_set_bdaddr_rome;

	return ret;
}