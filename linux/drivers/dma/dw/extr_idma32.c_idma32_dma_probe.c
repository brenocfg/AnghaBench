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
 int /*<<< orphan*/  idma32_block2bytes ; 
 int /*<<< orphan*/  idma32_bytes2block ; 
 int /*<<< orphan*/  idma32_disable ; 
 int /*<<< orphan*/  idma32_enable ; 
 int /*<<< orphan*/  idma32_encode_maxburst ; 
 int /*<<< orphan*/  idma32_initialize_chan ; 
 int /*<<< orphan*/  idma32_prepare_ctllo ; 
 int /*<<< orphan*/  idma32_resume_chan ; 
 int /*<<< orphan*/  idma32_set_device_name ; 
 int /*<<< orphan*/  idma32_suspend_chan ; 

int idma32_dma_probe(struct dw_dma_chip *chip)
{
	struct dw_dma *dw;

	dw = devm_kzalloc(chip->dev, sizeof(*dw), GFP_KERNEL);
	if (!dw)
		return -ENOMEM;

	/* Channel operations */
	dw->initialize_chan = idma32_initialize_chan;
	dw->suspend_chan = idma32_suspend_chan;
	dw->resume_chan = idma32_resume_chan;
	dw->prepare_ctllo = idma32_prepare_ctllo;
	dw->encode_maxburst = idma32_encode_maxburst;
	dw->bytes2block = idma32_bytes2block;
	dw->block2bytes = idma32_block2bytes;

	/* Device operations */
	dw->set_device_name = idma32_set_device_name;
	dw->disable = idma32_disable;
	dw->enable = idma32_enable;

	chip->dw = dw;
	return do_dma_probe(chip);
}