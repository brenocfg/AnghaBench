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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct hci_dev {int manufacturer; int /*<<< orphan*/  quirks; int /*<<< orphan*/  send; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  setup; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct btmtkuart_dev {int /*<<< orphan*/  vcc; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  pins_runtime; int /*<<< orphan*/  pinctrl; scalar_t__ boot; scalar_t__ reset; int /*<<< orphan*/  osc; int /*<<< orphan*/  pins_boot; struct hci_dev* hdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_work; struct serdev_device* serdev; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKUART_REQUIRED_WAKEUP ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_QUIRK_NON_PERSISTENT_SETUP ; 
 int /*<<< orphan*/  HCI_UART ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmtkuart_client_ops ; 
 int /*<<< orphan*/  btmtkuart_close ; 
 int /*<<< orphan*/  btmtkuart_flush ; 
 scalar_t__ btmtkuart_is_standalone (struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  btmtkuart_open ; 
 int btmtkuart_parse_dt (struct serdev_device*) ; 
 int /*<<< orphan*/  btmtkuart_send_frame ; 
 int /*<<< orphan*/  btmtkuart_setup ; 
 int /*<<< orphan*/  btmtkuart_shutdown ; 
 int /*<<< orphan*/  btmtkuart_tx_work ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_put (int /*<<< orphan*/ *,scalar_t__) ; 
 struct btmtkuart_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_client_ops (struct serdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int btmtkuart_probe(struct serdev_device *serdev)
{
	struct btmtkuart_dev *bdev;
	struct hci_dev *hdev;
	int err;

	bdev = devm_kzalloc(&serdev->dev, sizeof(*bdev), GFP_KERNEL);
	if (!bdev)
		return -ENOMEM;

	bdev->data = of_device_get_match_data(&serdev->dev);
	if (!bdev->data)
		return -ENODEV;

	bdev->serdev = serdev;
	serdev_device_set_drvdata(serdev, bdev);

	serdev_device_set_client_ops(serdev, &btmtkuart_client_ops);

	err = btmtkuart_parse_dt(serdev);
	if (err < 0)
		return err;

	INIT_WORK(&bdev->tx_work, btmtkuart_tx_work);
	skb_queue_head_init(&bdev->txq);

	/* Initialize and register HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		dev_err(&serdev->dev, "Can't allocate HCI device\n");
		return -ENOMEM;
	}

	bdev->hdev = hdev;

	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, bdev);

	hdev->open     = btmtkuart_open;
	hdev->close    = btmtkuart_close;
	hdev->flush    = btmtkuart_flush;
	hdev->setup    = btmtkuart_setup;
	hdev->shutdown = btmtkuart_shutdown;
	hdev->send     = btmtkuart_send_frame;
	SET_HCIDEV_DEV(hdev, &serdev->dev);

	hdev->manufacturer = 70;
	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);

	if (btmtkuart_is_standalone(bdev)) {
		err = clk_prepare_enable(bdev->osc);
		if (err < 0)
			return err;

		if (bdev->boot) {
			gpiod_set_value_cansleep(bdev->boot, 1);
		} else {
			/* Switch to the specific pin state for the booting
			 * requires.
			 */
			pinctrl_select_state(bdev->pinctrl, bdev->pins_boot);
		}

		/* Power on */
		err = regulator_enable(bdev->vcc);
		if (err < 0) {
			clk_disable_unprepare(bdev->osc);
			return err;
		}

		/* Reset if the reset-gpios is available otherwise the board
		 * -level design should be guaranteed.
		 */
		if (bdev->reset) {
			gpiod_set_value_cansleep(bdev->reset, 1);
			usleep_range(1000, 2000);
			gpiod_set_value_cansleep(bdev->reset, 0);
		}

		/* Wait some time until device got ready and switch to the pin
		 * mode the device requires for UART transfers.
		 */
		msleep(50);

		if (bdev->boot)
			devm_gpiod_put(&serdev->dev, bdev->boot);

		pinctrl_select_state(bdev->pinctrl, bdev->pins_runtime);

		/* A standalone device doesn't depends on power domain on SoC,
		 * so mark it as no callbacks.
		 */
		pm_runtime_no_callbacks(&serdev->dev);

		set_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state);
	}

	err = hci_register_dev(hdev);
	if (err < 0) {
		dev_err(&serdev->dev, "Can't register HCI device\n");
		hci_free_dev(hdev);
		goto err_regulator_disable;
	}

	return 0;

err_regulator_disable:
	if (btmtkuart_is_standalone(bdev))
		regulator_disable(bdev->vcc);

	return err;
}