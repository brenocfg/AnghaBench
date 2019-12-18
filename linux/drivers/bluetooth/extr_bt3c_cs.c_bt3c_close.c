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
struct hci_dev {int dummy; } ;
struct bt3c_info {struct hci_dev* hdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bt3c_hci_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 

__attribute__((used)) static int bt3c_close(struct bt3c_info *info)
{
	struct hci_dev *hdev = info->hdev;

	if (!hdev)
		return -ENODEV;

	bt3c_hci_close(hdev);

	hci_unregister_dev(hdev);
	hci_free_dev(hdev);

	return 0;
}