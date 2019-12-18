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
struct a10codec_info {TYPE_1__* cfg; } ;
struct a10codec_chinfo {int /*<<< orphan*/  dir; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; struct a10codec_info* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mute ) (struct a10codec_info*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ADC_FIFOC (struct a10codec_info*) ; 
 int /*<<< orphan*/  AC_DAC_FIFOC (struct a10codec_info*) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  SUNXI_DMA_HALT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct a10codec_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a10codec_stop(struct a10codec_chinfo *ch)
{
	struct a10codec_info *sc = ch->parent;

	/* Disable DMA channel */
	SUNXI_DMA_HALT(ch->dmac, ch->dmachan);

	sc->cfg->mute(sc, 1, ch->dir);

	if (ch->dir == PCMDIR_PLAY) {
		/* Disable DAC DRQ */
		CODEC_WRITE(sc, AC_DAC_FIFOC(sc), 0);
	} else {
		/* Disable ADC DRQ */
		CODEC_WRITE(sc, AC_ADC_FIFOC(sc), 0);
	}
}