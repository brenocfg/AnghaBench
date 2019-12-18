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
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_device_id {scalar_t__ driver_data; } ;
struct hci_dev {int manufacturer; int /*<<< orphan*/  quirks; int /*<<< orphan*/  send; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  setup; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct btmtksdio_dev {int /*<<< orphan*/ * dev; struct hci_dev* hdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_work; struct sdio_func* func; void* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_QUIRK_NON_PERSISTENT_SETUP ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmtksdio_close ; 
 int /*<<< orphan*/  btmtksdio_flush ; 
 int /*<<< orphan*/  btmtksdio_open ; 
 int /*<<< orphan*/  btmtksdio_send_frame ; 
 int /*<<< orphan*/  btmtksdio_setup ; 
 int /*<<< orphan*/  btmtksdio_shutdown ; 
 int /*<<< orphan*/  btmtksdio_tx_work ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct btmtksdio_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btmtksdio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct btmtksdio_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtksdio_probe(struct sdio_func *func,
			   const struct sdio_device_id *id)
{
	struct btmtksdio_dev *bdev;
	struct hci_dev *hdev;
	int err;

	bdev = devm_kzalloc(&func->dev, sizeof(*bdev), GFP_KERNEL);
	if (!bdev)
		return -ENOMEM;

	bdev->data = (void *)id->driver_data;
	if (!bdev->data)
		return -ENODEV;

	bdev->dev = &func->dev;
	bdev->func = func;

	INIT_WORK(&bdev->tx_work, btmtksdio_tx_work);
	skb_queue_head_init(&bdev->txq);

	/* Initialize and register HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		dev_err(&func->dev, "Can't allocate HCI device\n");
		return -ENOMEM;
	}

	bdev->hdev = hdev;

	hdev->bus = HCI_SDIO;
	hci_set_drvdata(hdev, bdev);

	hdev->open     = btmtksdio_open;
	hdev->close    = btmtksdio_close;
	hdev->flush    = btmtksdio_flush;
	hdev->setup    = btmtksdio_setup;
	hdev->shutdown = btmtksdio_shutdown;
	hdev->send     = btmtksdio_send_frame;
	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->manufacturer = 70;
	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);

	err = hci_register_dev(hdev);
	if (err < 0) {
		dev_err(&func->dev, "Can't register HCI device\n");
		hci_free_dev(hdev);
		return err;
	}

	sdio_set_drvdata(func, bdev);

	/* pm_runtime_enable would be done after the firmware is being
	 * downloaded because the core layer probably already enables
	 * runtime PM for this func such as the case host->caps &
	 * MMC_CAP_POWER_OFF_CARD.
	 */
	if (pm_runtime_enabled(bdev->dev))
		pm_runtime_disable(bdev->dev);

	/* As explaination in drivers/mmc/core/sdio_bus.c tells us:
	 * Unbound SDIO functions are always suspended.
	 * During probe, the function is set active and the usage count
	 * is incremented.  If the driver supports runtime PM,
	 * it should call pm_runtime_put_noidle() in its probe routine and
	 * pm_runtime_get_noresume() in its remove routine.
	 *
	 * So, put a pm_runtime_put_noidle here !
	 */
	pm_runtime_put_noidle(bdev->dev);

	return 0;
}