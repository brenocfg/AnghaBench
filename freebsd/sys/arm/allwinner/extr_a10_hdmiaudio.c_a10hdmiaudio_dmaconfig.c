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
struct sunxi_dma_config {int dst_noincr; int /*<<< orphan*/  dst_drqtype; int /*<<< orphan*/  src_drqtype; int /*<<< orphan*/  dst_wait_cyc; int /*<<< orphan*/  src_wait_cyc; int /*<<< orphan*/  dst_blksize; int /*<<< orphan*/  src_blksize; int /*<<< orphan*/  dst_burst_len; int /*<<< orphan*/  src_burst_len; int /*<<< orphan*/  dst_width; int /*<<< orphan*/  src_width; } ;
struct a10hdmiaudio_chinfo {int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; } ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 int /*<<< orphan*/  DDMA_BLKSIZE ; 
 int /*<<< orphan*/  DDMA_WAIT_CYC ; 
 int /*<<< orphan*/  DMA_BURST_LEN ; 
 int /*<<< orphan*/  DMA_WIDTH ; 
 int /*<<< orphan*/  DRQTYPE_HDMIAUDIO ; 
 int /*<<< orphan*/  DRQTYPE_SDRAM ; 
 int /*<<< orphan*/  SUNXI_DMA_SET_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sunxi_dma_config*) ; 
 int /*<<< orphan*/  memset (struct sunxi_dma_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
a10hdmiaudio_dmaconfig(struct a10hdmiaudio_chinfo *ch)
{
	struct sunxi_dma_config conf;

	memset(&conf, 0, sizeof(conf));
	conf.src_width = conf.dst_width = DMA_WIDTH;
	conf.src_burst_len = conf.dst_burst_len = DMA_BURST_LEN;
	conf.src_blksize = conf.dst_blksize = DDMA_BLKSIZE;
	conf.src_wait_cyc = conf.dst_wait_cyc = DDMA_WAIT_CYC;
	conf.src_drqtype = DRQTYPE_SDRAM;
	conf.dst_drqtype = DRQTYPE_HDMIAUDIO;
	conf.dst_noincr = true;

	SUNXI_DMA_SET_CONFIG(ch->dmac, ch->dmachan, &conf);
}