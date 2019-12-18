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
struct rsi_proto_ops {scalar_t__ (* get_host_intf ) (void*) ;int /*<<< orphan*/  (* set_bt_context ) (void*,struct rsi_hci_adapter*) ;} ;
struct rsi_hci_adapter {struct hci_dev* hdev; struct rsi_proto_ops* proto_ops; void* priv; } ;
struct hci_dev {int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_PRIMARY ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  HCI_USB ; 
 scalar_t__ RSI_HOST_INTF_SDIO ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct rsi_hci_adapter*) ; 
 int /*<<< orphan*/  kfree (struct rsi_hci_adapter*) ; 
 struct rsi_hci_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_hci_close ; 
 int /*<<< orphan*/  rsi_hci_flush ; 
 int /*<<< orphan*/  rsi_hci_open ; 
 int /*<<< orphan*/  rsi_hci_send_pkt ; 
 int /*<<< orphan*/  stub1 (void*,struct rsi_hci_adapter*) ; 
 scalar_t__ stub2 (void*) ; 

__attribute__((used)) static int rsi_hci_attach(void *priv, struct rsi_proto_ops *ops)
{
	struct rsi_hci_adapter *h_adapter = NULL;
	struct hci_dev *hdev;
	int err = 0;

	h_adapter = kzalloc(sizeof(*h_adapter), GFP_KERNEL);
	if (!h_adapter)
		return -ENOMEM;

	h_adapter->priv = priv;
	ops->set_bt_context(priv, h_adapter);
	h_adapter->proto_ops = ops;

	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Failed to alloc HCI device");
		goto err;
	}

	h_adapter->hdev = hdev;

	if (ops->get_host_intf(priv) == RSI_HOST_INTF_SDIO)
		hdev->bus = HCI_SDIO;
	else
		hdev->bus = HCI_USB;

	hci_set_drvdata(hdev, h_adapter);
	hdev->dev_type = HCI_PRIMARY;
	hdev->open = rsi_hci_open;
	hdev->close = rsi_hci_close;
	hdev->flush = rsi_hci_flush;
	hdev->send = rsi_hci_send_pkt;

	err = hci_register_dev(hdev);
	if (err < 0) {
		BT_ERR("HCI registration failed with errcode %d", err);
		hci_free_dev(hdev);
		goto err;
	}

	return 0;
err:
	h_adapter->hdev = NULL;
	kfree(h_adapter);
	return -EINVAL;
}