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
struct sdio_func {int dummy; } ;
struct btmrvl_sdio_card {TYPE_1__* priv; } ;
struct TYPE_3__ {int surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  MODULE_SHUTDOWN_REQ ; 
 int /*<<< orphan*/  btmrvl_remove_card (TYPE_1__*) ; 
 int /*<<< orphan*/  btmrvl_sdio_disable_host_int (struct btmrvl_sdio_card*) ; 
 int /*<<< orphan*/  btmrvl_sdio_unregister_dev (struct btmrvl_sdio_card*) ; 
 int /*<<< orphan*/  btmrvl_send_module_cfg_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct btmrvl_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 scalar_t__ user_rmmod ; 

__attribute__((used)) static void btmrvl_sdio_remove(struct sdio_func *func)
{
	struct btmrvl_sdio_card *card;

	if (func) {
		card = sdio_get_drvdata(func);
		if (card) {
			/* Send SHUTDOWN command & disable interrupt
			 * if user removes the module.
			 */
			if (user_rmmod) {
				btmrvl_send_module_cfg_cmd(card->priv,
							MODULE_SHUTDOWN_REQ);
				btmrvl_sdio_disable_host_int(card);
			}
			BT_DBG("unregister dev");
			card->priv->surprise_removed = true;
			btmrvl_sdio_unregister_dev(card);
			btmrvl_remove_card(card->priv);
		}
	}
}