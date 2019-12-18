#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hci_dev {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  set_bdaddr; int /*<<< orphan*/  setup; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  task; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_type; struct hci_dev* hcidev; } ;
struct btmrvl_private {TYPE_2__ main_thread; TYPE_1__ btmrvl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  btmrvl_close ; 
 int /*<<< orphan*/  btmrvl_debugfs_init (struct hci_dev*) ; 
 int /*<<< orphan*/  btmrvl_flush ; 
 int /*<<< orphan*/  btmrvl_free_adapter (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_open ; 
 int /*<<< orphan*/  btmrvl_send_frame ; 
 int /*<<< orphan*/  btmrvl_set_bdaddr ; 
 int /*<<< orphan*/  btmrvl_setup ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btmrvl_private*) ; 
 int /*<<< orphan*/  kfree (struct btmrvl_private*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

int btmrvl_register_hdev(struct btmrvl_private *priv)
{
	struct hci_dev *hdev = NULL;
	int ret;

	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Can not allocate HCI device");
		goto err_hdev;
	}

	priv->btmrvl_dev.hcidev = hdev;
	hci_set_drvdata(hdev, priv);

	hdev->bus   = HCI_SDIO;
	hdev->open  = btmrvl_open;
	hdev->close = btmrvl_close;
	hdev->flush = btmrvl_flush;
	hdev->send  = btmrvl_send_frame;
	hdev->setup = btmrvl_setup;
	hdev->set_bdaddr = btmrvl_set_bdaddr;

	hdev->dev_type = priv->btmrvl_dev.dev_type;

	ret = hci_register_dev(hdev);
	if (ret < 0) {
		BT_ERR("Can not register HCI device");
		goto err_hci_register_dev;
	}

#ifdef CONFIG_DEBUG_FS
	btmrvl_debugfs_init(hdev);
#endif

	return 0;

err_hci_register_dev:
	hci_free_dev(hdev);

err_hdev:
	/* Stop the thread servicing the interrupts */
	kthread_stop(priv->main_thread.task);

	btmrvl_free_adapter(priv);
	kfree(priv);

	return -ENOMEM;
}