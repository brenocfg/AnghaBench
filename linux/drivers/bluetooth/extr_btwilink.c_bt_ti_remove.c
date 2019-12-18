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
struct ti_st {struct hci_dev* hdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 struct ti_st* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  ti_st_close (struct hci_dev*) ; 

__attribute__((used)) static int bt_ti_remove(struct platform_device *pdev)
{
	struct hci_dev *hdev;
	struct ti_st *hst = dev_get_drvdata(&pdev->dev);

	if (!hst)
		return -EFAULT;

	BT_DBG("%s", hst->hdev->name);

	hdev = hst->hdev;
	ti_st_close(hdev);
	hci_unregister_dev(hdev);

	hci_free_dev(hdev);

	dev_set_drvdata(&pdev->dev, NULL);
	return 0;
}