#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hci_dev {int /*<<< orphan*/  set_bdaddr; int /*<<< orphan*/  setup; int /*<<< orphan*/  send; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct btqcomsmd {struct hci_dev* hdev; void* cmd_channel; void* acl_channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_SMD ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  btqcomsmd_acl_callback ; 
 int /*<<< orphan*/  btqcomsmd_close ; 
 int /*<<< orphan*/  btqcomsmd_cmd_callback ; 
 int /*<<< orphan*/  btqcomsmd_open ; 
 int /*<<< orphan*/  btqcomsmd_send ; 
 int /*<<< orphan*/  btqcomsmd_setup ; 
 void* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct btqcomsmd* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btqcomsmd*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct btqcomsmd*) ; 
 int /*<<< orphan*/  qca_set_bdaddr_rome ; 
 void* qcom_wcnss_open_channel (void*,char*,int /*<<< orphan*/ ,struct btqcomsmd*) ; 

__attribute__((used)) static int btqcomsmd_probe(struct platform_device *pdev)
{
	struct btqcomsmd *btq;
	struct hci_dev *hdev;
	void *wcnss;
	int ret;

	btq = devm_kzalloc(&pdev->dev, sizeof(*btq), GFP_KERNEL);
	if (!btq)
		return -ENOMEM;

	wcnss = dev_get_drvdata(pdev->dev.parent);

	btq->acl_channel = qcom_wcnss_open_channel(wcnss, "APPS_RIVA_BT_ACL",
						   btqcomsmd_acl_callback, btq);
	if (IS_ERR(btq->acl_channel))
		return PTR_ERR(btq->acl_channel);

	btq->cmd_channel = qcom_wcnss_open_channel(wcnss, "APPS_RIVA_BT_CMD",
						   btqcomsmd_cmd_callback, btq);
	if (IS_ERR(btq->cmd_channel))
		return PTR_ERR(btq->cmd_channel);

	hdev = hci_alloc_dev();
	if (!hdev)
		return -ENOMEM;

	hci_set_drvdata(hdev, btq);
	btq->hdev = hdev;
	SET_HCIDEV_DEV(hdev, &pdev->dev);

	hdev->bus = HCI_SMD;
	hdev->open = btqcomsmd_open;
	hdev->close = btqcomsmd_close;
	hdev->send = btqcomsmd_send;
	hdev->setup = btqcomsmd_setup;
	hdev->set_bdaddr = qca_set_bdaddr_rome;

	ret = hci_register_dev(hdev);
	if (ret < 0) {
		hci_free_dev(hdev);
		return ret;
	}

	platform_set_drvdata(pdev, btq);

	return 0;
}