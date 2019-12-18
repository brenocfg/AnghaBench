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
struct qca_serdev {int /*<<< orphan*/  oper_speed; int /*<<< orphan*/  init_speed; int /*<<< orphan*/  bt_en; int /*<<< orphan*/  btsoc_type; } ;
struct qca_data {int /*<<< orphan*/  wake_retrans; int /*<<< orphan*/  tx_idle_delay; int /*<<< orphan*/  tx_idle_timer; int /*<<< orphan*/  wake_retrans_timer; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  vote_last_jif; int /*<<< orphan*/  rx_ibs_state; int /*<<< orphan*/  tx_ibs_state; int /*<<< orphan*/  drop_ev_comp; struct hci_uart* hu; int /*<<< orphan*/  ws_tx_vote_off; int /*<<< orphan*/  ws_rx_vote_off; int /*<<< orphan*/  ws_awake_device; int /*<<< orphan*/  ws_awake_rx; int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  tx_wait_q; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct qca_data* priv; int /*<<< orphan*/  oper_speed; int /*<<< orphan*/  init_speed; scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_IBS_RX_ASLEEP ; 
 int /*<<< orphan*/  HCI_IBS_TX_ASLEEP ; 
 int /*<<< orphan*/  IBS_TX_IDLE_TIMEOUT_MS ; 
 int /*<<< orphan*/  IBS_WAKE_RETRANS_TIMEOUT_MS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hci_ibs_tx_idle_timeout ; 
 int /*<<< orphan*/  hci_ibs_wake_retrans_timeout ; 
 int /*<<< orphan*/  hci_uart_has_flow_control (struct hci_uart*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct qca_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct qca_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qca_is_wcn399x (int /*<<< orphan*/ ) ; 
 int qca_power_setup (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_wq_awake_device ; 
 int /*<<< orphan*/  qca_wq_awake_rx ; 
 int /*<<< orphan*/  qca_wq_serial_rx_clock_vote_off ; 
 int /*<<< orphan*/  qca_wq_serial_tx_clock_vote_off ; 
 struct qca_serdev* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_open(struct hci_uart *hu)
{
	struct qca_serdev *qcadev;
	struct qca_data *qca;
	int ret;

	BT_DBG("hu %p qca_open", hu);

	if (!hci_uart_has_flow_control(hu))
		return -EOPNOTSUPP;

	qca = kzalloc(sizeof(struct qca_data), GFP_KERNEL);
	if (!qca)
		return -ENOMEM;

	skb_queue_head_init(&qca->txq);
	skb_queue_head_init(&qca->tx_wait_q);
	spin_lock_init(&qca->hci_ibs_lock);
	qca->workqueue = alloc_ordered_workqueue("qca_wq", 0);
	if (!qca->workqueue) {
		BT_ERR("QCA Workqueue not initialized properly");
		kfree(qca);
		return -ENOMEM;
	}

	INIT_WORK(&qca->ws_awake_rx, qca_wq_awake_rx);
	INIT_WORK(&qca->ws_awake_device, qca_wq_awake_device);
	INIT_WORK(&qca->ws_rx_vote_off, qca_wq_serial_rx_clock_vote_off);
	INIT_WORK(&qca->ws_tx_vote_off, qca_wq_serial_tx_clock_vote_off);

	qca->hu = hu;
	init_completion(&qca->drop_ev_comp);

	/* Assume we start with both sides asleep -- extra wakes OK */
	qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
	qca->rx_ibs_state = HCI_IBS_RX_ASLEEP;

	qca->vote_last_jif = jiffies;

	hu->priv = qca;

	if (hu->serdev) {

		qcadev = serdev_device_get_drvdata(hu->serdev);
		if (!qca_is_wcn399x(qcadev->btsoc_type)) {
			gpiod_set_value_cansleep(qcadev->bt_en, 1);
			/* Controller needs time to bootup. */
			msleep(150);
		} else {
			hu->init_speed = qcadev->init_speed;
			hu->oper_speed = qcadev->oper_speed;
			ret = qca_power_setup(hu, true);
			if (ret) {
				destroy_workqueue(qca->workqueue);
				kfree_skb(qca->rx_skb);
				hu->priv = NULL;
				kfree(qca);
				return ret;
			}
		}
	}

	timer_setup(&qca->wake_retrans_timer, hci_ibs_wake_retrans_timeout, 0);
	qca->wake_retrans = IBS_WAKE_RETRANS_TIMEOUT_MS;

	timer_setup(&qca->tx_idle_timer, hci_ibs_tx_idle_timeout, 0);
	qca->tx_idle_delay = IBS_TX_IDLE_TIMEOUT_MS;

	BT_DBG("HCI_UART_QCA open, tx_idle_delay=%u, wake_retrans=%u",
	       qca->tx_idle_delay, qca->wake_retrans);

	return 0;
}