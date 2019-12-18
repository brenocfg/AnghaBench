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
typedef  int /*<<< orphan*/  u8 ;
struct hci_uart {int /*<<< orphan*/  serdev; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TRANS_TIMEOUT_MS ; 
 int /*<<< orphan*/  QCA_WCN3990_POWEROFF_PULSE ; 
 int /*<<< orphan*/  QCA_WCN3990_POWERON_PULSE ; 
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  serdev_device_wait_until_sent (int /*<<< orphan*/ ,int) ; 
 int serdev_device_write_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serdev_device_write_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_send_power_pulse(struct hci_uart *hu, bool on)
{
	int ret;
	int timeout = msecs_to_jiffies(CMD_TRANS_TIMEOUT_MS);
	u8 cmd = on ? QCA_WCN3990_POWERON_PULSE : QCA_WCN3990_POWEROFF_PULSE;

	/* These power pulses are single byte command which are sent
	 * at required baudrate to wcn3990. On wcn3990, we have an external
	 * circuit at Tx pin which decodes the pulse sent at specific baudrate.
	 * For example, wcn3990 supports RF COEX antenna for both Wi-Fi/BT
	 * and also we use the same power inputs to turn on and off for
	 * Wi-Fi/BT. Powering up the power sources will not enable BT, until
	 * we send a power on pulse at 115200 bps. This algorithm will help to
	 * save power. Disabling hardware flow control is mandatory while
	 * sending power pulses to SoC.
	 */
	bt_dev_dbg(hu->hdev, "sending power pulse %02x to controller", cmd);

	serdev_device_write_flush(hu->serdev);
	hci_uart_set_flow_control(hu, true);
	ret = serdev_device_write_buf(hu->serdev, &cmd, sizeof(cmd));
	if (ret < 0) {
		bt_dev_err(hu->hdev, "failed to send power pulse %02x", cmd);
		return ret;
	}

	serdev_device_wait_until_sent(hu->serdev, timeout);
	hci_uart_set_flow_control(hu, false);

	/* Give to controller time to boot/shutdown */
	if (on)
		msleep(100);
	else
		msleep(10);

	return 0;
}