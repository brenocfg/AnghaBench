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
struct dw_dma_chip {struct dw_dma* dw; int /*<<< orphan*/  dev; } ;
struct dw_dma {int /*<<< orphan*/  enable; int /*<<< orphan*/  disable; int /*<<< orphan*/  set_device_name; int /*<<< orphan*/  block2bytes; int /*<<< orphan*/  bytes2block; int /*<<< orphan*/  encode_maxburst; int /*<<< orphan*/  prepare_ctllo; int /*<<< orphan*/  resume_chan; int /*<<< orphan*/  suspend_chan; int /*<<< orphan*/  initialize_chan; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dw_dma* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int do_dma_probe (struct dw_dma_chip*) ; 
 int /*<<< orphan*/  dw_dma_block2bytes ; 
 int /*<<< orphan*/  dw_dma_bytes2block ; 
 int /*<<< orphan*/  dw_dma_disable ; 
 int /*<<< orphan*/  dw_dma_enable ; 
 int /*<<< orphan*/  dw_dma_encode_maxburst ; 
 int /*<<< orphan*/  dw_dma_initialize_chan ; 
 int /*<<< orphan*/  dw_dma_prepare_ctllo ; 
 int /*<<< orphan*/  dw_dma_resume_chan ; 
 int /*<<< orphan*/  dw_dma_set_device_name ; 
 int /*<<< orphan*/  dw_dma_suspend_chan ; 

int dw_dma_probe(struct dw_dma_chip *chip)
{
	struct dw_dma *dw;

	dw = devm_kzalloc(chip->dev, sizeof(*dw), GFP_KERNEL);
	if (!dw)
		return -ENOMEM;

	/* Channel operations */
	dw->initialize_chan = dw_dma_initialize_chan;
	dw->suspend_chan = dw_dma_suspend_chan;
	dw->resume_chan = dw_dma_resume_chan;
	dw->prepare_ctllo = dw_dma_prepare_ctllo;
	dw->encode_maxburst = dw_dma_encode_maxburst;
	dw->bytes2block = dw_dma_bytes2block;
	dw->block2bytes = dw_dma_block2bytes;

	/* Device operations */
	dw->set_device_name = dw_dma_set_device_name;
	dw->disable = dw_dma_disable;
	dw->enable = dw_dma_enable;

	chip->dw = dw;
	return do_dma_probe(chip);
}