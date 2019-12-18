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
struct hci_dev {int /*<<< orphan*/  quirks; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_STRICT_DUPLICATE_FILTER ; 
 int /*<<< orphan*/  btbcm_check_bdaddr (struct hci_dev*) ; 
 int btbcm_initialize (struct hci_dev*,char*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btbcm_finalize(struct hci_dev *hdev)
{
	char fw_name[64];
	int err;

	/* Re-initialize */
	err = btbcm_initialize(hdev, fw_name, sizeof(fw_name), true);
	if (err)
		return err;

	btbcm_check_bdaddr(hdev);

	set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);

	return 0;
}