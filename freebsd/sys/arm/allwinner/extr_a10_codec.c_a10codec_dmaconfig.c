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
struct sunxi_dma_config {int src_width; int dst_width; int src_burst_len; int dst_burst_len; int dst_noincr; int src_noincr; int /*<<< orphan*/  dst_drqtype; int /*<<< orphan*/  src_drqtype; } ;
struct a10codec_info {TYPE_1__* cfg; } ;
struct a10codec_chinfo {scalar_t__ dir; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; struct a10codec_info* parent; } ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_2__ {int /*<<< orphan*/  drqtype_sdram; int /*<<< orphan*/  drqtype_codec; } ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  SUNXI_DMA_SET_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sunxi_dma_config*) ; 
 int /*<<< orphan*/  memset (struct sunxi_dma_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
a10codec_dmaconfig(struct a10codec_chinfo *ch)
{
	struct a10codec_info *sc = ch->parent;
	struct sunxi_dma_config conf;

	memset(&conf, 0, sizeof(conf));
	conf.src_width = conf.dst_width = 16;
	conf.src_burst_len = conf.dst_burst_len = 4;

	if (ch->dir == PCMDIR_PLAY) {
		conf.dst_noincr = true;
		conf.src_drqtype = sc->cfg->drqtype_sdram;
		conf.dst_drqtype = sc->cfg->drqtype_codec;
	} else {
		conf.src_noincr = true;
		conf.src_drqtype = sc->cfg->drqtype_codec;
		conf.dst_drqtype = sc->cfg->drqtype_sdram;
	}

	SUNXI_DMA_SET_CONFIG(ch->dmac, ch->dmachan, &conf);
}