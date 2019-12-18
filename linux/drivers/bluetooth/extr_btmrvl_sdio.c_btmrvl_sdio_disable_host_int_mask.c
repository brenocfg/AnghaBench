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
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_sdio_card {TYPE_1__* reg; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_int_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_disable_host_int_mask(struct btmrvl_sdio_card *card,
								u8 mask)
{
	u8 host_int_mask;
	int ret;

	host_int_mask = sdio_readb(card->func, card->reg->host_int_mask, &ret);
	if (ret)
		return -EIO;

	host_int_mask &= ~mask;

	sdio_writeb(card->func, host_int_mask, card->reg->host_int_mask, &ret);
	if (ret < 0) {
		BT_ERR("Unable to disable the host interrupt!");
		return -EIO;
	}

	return 0;
}