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
struct btmtksdio_dev {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct btmtksdio_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtksdio_flush(struct hci_dev *hdev)
{
	struct btmtksdio_dev *bdev = hci_get_drvdata(hdev);

	skb_queue_purge(&bdev->txq);

	cancel_work_sync(&bdev->tx_work);

	return 0;
}