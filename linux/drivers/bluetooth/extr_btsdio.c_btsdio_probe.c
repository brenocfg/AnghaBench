#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdio_func_tuple {struct sdio_func_tuple* next; int /*<<< orphan*/  size; int /*<<< orphan*/  code; } ;
struct sdio_func {int vendor; int device; int /*<<< orphan*/  dev; TYPE_1__* card; int /*<<< orphan*/  class; struct sdio_func_tuple* tuples; } ;
struct sdio_device_id {scalar_t__ class; } ;
struct hci_dev {int /*<<< orphan*/  quirks; int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  bus; } ;
struct btsdio_data {struct hci_dev* hdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  work; struct sdio_func* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sdio_func*,struct sdio_device_id const*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_AMP ; 
 int /*<<< orphan*/  HCI_PRIMARY ; 
 int /*<<< orphan*/  HCI_QUIRK_RESET_ON_CLOSE ; 
 int /*<<< orphan*/  HCI_SDIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SDIO_CLASS_BT_AMP ; 
#define  SDIO_DEVICE_ID_BROADCOM_43341 130 
#define  SDIO_DEVICE_ID_BROADCOM_43430 129 
#define  SDIO_DEVICE_ID_BROADCOM_4356 128 
 int SDIO_VENDOR_ID_BROADCOM ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsdio_close ; 
 int /*<<< orphan*/  btsdio_flush ; 
 int /*<<< orphan*/  btsdio_open ; 
 int /*<<< orphan*/  btsdio_send_frame ; 
 int /*<<< orphan*/  btsdio_work ; 
 struct btsdio_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btsdio_data*) ; 
 int /*<<< orphan*/  mmc_card_is_removable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct btsdio_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btsdio_probe(struct sdio_func *func,
				const struct sdio_device_id *id)
{
	struct btsdio_data *data;
	struct hci_dev *hdev;
	struct sdio_func_tuple *tuple = func->tuples;
	int err;

	BT_DBG("func %p id %p class 0x%04x", func, id, func->class);

	while (tuple) {
		BT_DBG("code 0x%x size %d", tuple->code, tuple->size);
		tuple = tuple->next;
	}

	/* Broadcom devices soldered onto the PCB (non-removable) use an
	 * UART connection for Bluetooth, ignore the BT SDIO interface.
	 */
	if (func->vendor == SDIO_VENDOR_ID_BROADCOM &&
	    !mmc_card_is_removable(func->card->host)) {
		switch (func->device) {
		case SDIO_DEVICE_ID_BROADCOM_43341:
		case SDIO_DEVICE_ID_BROADCOM_43430:
		case SDIO_DEVICE_ID_BROADCOM_4356:
			return -ENODEV;
		}
	}

	data = devm_kzalloc(&func->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->func = func;

	INIT_WORK(&data->work, btsdio_work);

	skb_queue_head_init(&data->txq);

	hdev = hci_alloc_dev();
	if (!hdev)
		return -ENOMEM;

	hdev->bus = HCI_SDIO;
	hci_set_drvdata(hdev, data);

	if (id->class == SDIO_CLASS_BT_AMP)
		hdev->dev_type = HCI_AMP;
	else
		hdev->dev_type = HCI_PRIMARY;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->open     = btsdio_open;
	hdev->close    = btsdio_close;
	hdev->flush    = btsdio_flush;
	hdev->send     = btsdio_send_frame;

	if (func->vendor == 0x0104 && func->device == 0x00c5)
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	err = hci_register_dev(hdev);
	if (err < 0) {
		hci_free_dev(hdev);
		return err;
	}

	sdio_set_drvdata(func, data);

	return 0;
}