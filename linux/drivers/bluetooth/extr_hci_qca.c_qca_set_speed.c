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
struct qca_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  drop_ev_comp; } ;
struct hci_uart {int /*<<< orphan*/  hdev; struct qca_data* priv; } ;
typedef  enum qca_speed_type { ____Placeholder_qca_speed_type } qca_speed_type ;
typedef  enum qca_btsoc_type { ____Placeholder_qca_btsoc_type } qca_btsoc_type ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QCA_DROP_VENDOR_EVENT ; 
 int QCA_INIT_SPEED ; 
 int QCA_OPER_SPEED ; 
 int QCA_WCN3990 ; 
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,unsigned int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 unsigned int qca_get_baudrate_value (unsigned int) ; 
 unsigned int qca_get_speed (struct hci_uart*,int) ; 
 scalar_t__ qca_is_wcn399x (int) ; 
 int qca_set_baudrate (int /*<<< orphan*/ ,unsigned int) ; 
 int qca_soc_type (struct hci_uart*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_set_speed(struct hci_uart *hu, enum qca_speed_type speed_type)
{
	unsigned int speed, qca_baudrate;
	struct qca_data *qca = hu->priv;
	int ret = 0;

	if (speed_type == QCA_INIT_SPEED) {
		speed = qca_get_speed(hu, QCA_INIT_SPEED);
		if (speed)
			host_set_baudrate(hu, speed);
	} else {
		enum qca_btsoc_type soc_type = qca_soc_type(hu);

		speed = qca_get_speed(hu, QCA_OPER_SPEED);
		if (!speed)
			return 0;

		/* Disable flow control for wcn3990 to deassert RTS while
		 * changing the baudrate of chip and host.
		 */
		if (qca_is_wcn399x(soc_type))
			hci_uart_set_flow_control(hu, true);

		if (soc_type == QCA_WCN3990) {
			reinit_completion(&qca->drop_ev_comp);
			set_bit(QCA_DROP_VENDOR_EVENT, &qca->flags);
		}

		qca_baudrate = qca_get_baudrate_value(speed);
		bt_dev_dbg(hu->hdev, "Set UART speed to %d", speed);
		ret = qca_set_baudrate(hu->hdev, qca_baudrate);
		if (ret)
			goto error;

		host_set_baudrate(hu, speed);

error:
		if (qca_is_wcn399x(soc_type))
			hci_uart_set_flow_control(hu, false);

		if (soc_type == QCA_WCN3990) {
			/* Wait for the controller to send the vendor event
			 * for the baudrate change command.
			 */
			if (!wait_for_completion_timeout(&qca->drop_ev_comp,
						 msecs_to_jiffies(100))) {
				bt_dev_err(hu->hdev,
					   "Failed to change controller baudrate\n");
				ret = -ETIMEDOUT;
			}

			clear_bit(QCA_DROP_VENDOR_EVENT, &qca->flags);
		}
	}

	return ret;
}