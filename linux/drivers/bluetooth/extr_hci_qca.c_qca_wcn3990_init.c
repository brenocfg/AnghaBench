#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qca_serdev {TYPE_1__* bt_power; } ;
struct hci_uart {int /*<<< orphan*/  hdev; int /*<<< orphan*/  serdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vregs_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA_INIT_SPEED ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,int) ; 
 int qca_power_setup (struct hci_uart*,int) ; 
 int qca_send_power_pulse (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_set_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_close (int /*<<< orphan*/ ) ; 
 struct qca_serdev* serdev_device_get_drvdata (int /*<<< orphan*/ ) ; 
 int serdev_device_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_wcn3990_init(struct hci_uart *hu)
{
	struct qca_serdev *qcadev;
	int ret;

	/* Check for vregs status, may be hci down has turned
	 * off the voltage regulator.
	 */
	qcadev = serdev_device_get_drvdata(hu->serdev);
	if (!qcadev->bt_power->vregs_on) {
		serdev_device_close(hu->serdev);
		ret = qca_power_setup(hu, true);
		if (ret)
			return ret;

		ret = serdev_device_open(hu->serdev);
		if (ret) {
			bt_dev_err(hu->hdev, "failed to open port");
			return ret;
		}
	}

	/* Forcefully enable wcn3990 to enter in to boot mode. */
	host_set_baudrate(hu, 2400);
	ret = qca_send_power_pulse(hu, false);
	if (ret)
		return ret;

	qca_set_speed(hu, QCA_INIT_SPEED);
	ret = qca_send_power_pulse(hu, true);
	if (ret)
		return ret;

	/* Now the device is in ready state to communicate with host.
	 * To sync host with device we need to reopen port.
	 * Without this, we will have RTS and CTS synchronization
	 * issues.
	 */
	serdev_device_close(hu->serdev);
	ret = serdev_device_open(hu->serdev);
	if (ret) {
		bt_dev_err(hu->hdev, "failed to open port");
		return ret;
	}

	hci_uart_set_flow_control(hu, false);

	return 0;
}