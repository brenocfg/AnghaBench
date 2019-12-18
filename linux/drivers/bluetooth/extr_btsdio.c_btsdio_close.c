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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btsdio_data {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EN_INTRD ; 
 struct btsdio_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btsdio_close(struct hci_dev *hdev)
{
	struct btsdio_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	sdio_claim_host(data->func);

	sdio_writeb(data->func, 0x00, REG_EN_INTRD, NULL);

	sdio_release_irq(data->func);
	sdio_disable_func(data->func);

	sdio_release_host(data->func);

	return 0;
}