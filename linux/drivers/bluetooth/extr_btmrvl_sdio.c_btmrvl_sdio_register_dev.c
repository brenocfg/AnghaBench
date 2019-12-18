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
typedef  int u8 ;
struct sdio_func {int /*<<< orphan*/  num; } ;
struct btmrvl_sdio_card {int ioport; TYPE_1__* reg; struct sdio_func* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_misc_cfg; int /*<<< orphan*/  host_int_rsr; scalar_t__ int_read_to_clear; int /*<<< orphan*/  io_port_2; int /*<<< orphan*/  io_port_1; int /*<<< orphan*/  io_port_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  btmrvl_sdio_interrupt ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int sdio_readb (struct sdio_func*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct btmrvl_sdio_card*) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_register_dev(struct btmrvl_sdio_card *card)
{
	struct sdio_func *func;
	u8 reg;
	int ret;

	if (!card || !card->func) {
		BT_ERR("Error: card or function is NULL!");
		ret = -EINVAL;
		goto failed;
	}

	func = card->func;

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	if (ret) {
		BT_ERR("sdio_enable_func() failed: ret=%d", ret);
		ret = -EIO;
		goto release_host;
	}

	ret = sdio_claim_irq(func, btmrvl_sdio_interrupt);
	if (ret) {
		BT_ERR("sdio_claim_irq failed: ret=%d", ret);
		ret = -EIO;
		goto disable_func;
	}

	ret = sdio_set_block_size(card->func, SDIO_BLOCK_SIZE);
	if (ret) {
		BT_ERR("cannot set SDIO block size");
		ret = -EIO;
		goto release_irq;
	}

	reg = sdio_readb(func, card->reg->io_port_0, &ret);
	if (ret < 0) {
		ret = -EIO;
		goto release_irq;
	}

	card->ioport = reg;

	reg = sdio_readb(func, card->reg->io_port_1, &ret);
	if (ret < 0) {
		ret = -EIO;
		goto release_irq;
	}

	card->ioport |= (reg << 8);

	reg = sdio_readb(func, card->reg->io_port_2, &ret);
	if (ret < 0) {
		ret = -EIO;
		goto release_irq;
	}

	card->ioport |= (reg << 16);

	BT_DBG("SDIO FUNC%d IO port: 0x%x", func->num, card->ioport);

	if (card->reg->int_read_to_clear) {
		reg = sdio_readb(func, card->reg->host_int_rsr, &ret);
		if (ret < 0) {
			ret = -EIO;
			goto release_irq;
		}
		sdio_writeb(func, reg | 0x3f, card->reg->host_int_rsr, &ret);
		if (ret < 0) {
			ret = -EIO;
			goto release_irq;
		}

		reg = sdio_readb(func, card->reg->card_misc_cfg, &ret);
		if (ret < 0) {
			ret = -EIO;
			goto release_irq;
		}
		sdio_writeb(func, reg | 0x10, card->reg->card_misc_cfg, &ret);
		if (ret < 0) {
			ret = -EIO;
			goto release_irq;
		}
	}

	sdio_set_drvdata(func, card);

	sdio_release_host(func);

	return 0;

release_irq:
	sdio_release_irq(func);

disable_func:
	sdio_disable_func(func);

release_host:
	sdio_release_host(func);

failed:
	return ret;
}