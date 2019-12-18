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
struct sdio_func {int dummy; } ;
struct hci_dev {int dummy; } ;
struct btsdio_data {struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sdio_func*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 struct btsdio_data* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btsdio_remove(struct sdio_func *func)
{
	struct btsdio_data *data = sdio_get_drvdata(func);
	struct hci_dev *hdev;

	BT_DBG("func %p", func);

	if (!data)
		return;

	hdev = data->hdev;

	sdio_set_drvdata(func, NULL);

	hci_unregister_dev(hdev);

	hci_free_dev(hdev);
}