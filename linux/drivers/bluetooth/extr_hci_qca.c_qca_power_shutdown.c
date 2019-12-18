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
struct qca_data {int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  flags; } ;
struct hci_uart {struct qca_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA_IBS_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_flush (struct hci_uart*) ; 
 int /*<<< orphan*/  qca_power_setup (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_send_power_pulse (struct hci_uart*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qca_power_shutdown(struct hci_uart *hu)
{
	struct qca_data *qca = hu->priv;
	unsigned long flags;

	/* From this point we go into power off state. But serial port is
	 * still open, stop queueing the IBS data and flush all the buffered
	 * data in skb's.
	 */
	spin_lock_irqsave(&qca->hci_ibs_lock, flags);
	clear_bit(QCA_IBS_ENABLED, &qca->flags);
	qca_flush(hu);
	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	host_set_baudrate(hu, 2400);
	qca_send_power_pulse(hu, false);
	qca_power_setup(hu, false);
}