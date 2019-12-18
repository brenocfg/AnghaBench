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
typedef  int uint32_t ;
struct a10codec_info {TYPE_1__* cfg; } ;
struct a10codec_chinfo {scalar_t__ dir; int /*<<< orphan*/  format; scalar_t__ pos; struct a10codec_info* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mute ) (struct a10codec_info*,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ADC_FIFOC (struct a10codec_info*) ; 
 int /*<<< orphan*/  AC_ADC_FIFOS (struct a10codec_info*) ; 
 int /*<<< orphan*/  AC_DAC_FIFOC (struct a10codec_info*) ; 
 int /*<<< orphan*/  AC_DAC_FIFOS (struct a10codec_info*) ; 
 int ADC_FIFOC_DRQ_EN ; 
 int ADC_FIFOC_EN_AD ; 
 int ADC_FIFOC_FIFO_FLUSH ; 
 int ADC_FIFOC_FS_SHIFT ; 
 int ADC_FIFOC_MONO_EN ; 
 int ADC_FIFOC_RX_FIFO_MODE ; 
 int ADC_FIFOC_RX_TRIG_LEVEL_SHIFT ; 
 int AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 int CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int) ; 
 int DAC_FIFOC_DRQ_CLR_CNT_SHIFT ; 
 int DAC_FIFOC_DRQ_EN ; 
 int DAC_FIFOC_FIFO_FLUSH ; 
 int DAC_FIFOC_FIFO_MODE_SHIFT ; 
 int DAC_FIFOC_FS_SHIFT ; 
 int DAC_FIFOC_MONO_EN ; 
 int DAC_FIFOC_TX_TRIG_LEVEL_SHIFT ; 
 int DRQ_CLR_CNT ; 
 int FIFO_MODE_16_15_0 ; 
 scalar_t__ PCMDIR_PLAY ; 
 int RX_TRIG_LEVEL ; 
 int TX_TRIG_LEVEL ; 
 int /*<<< orphan*/  a10codec_dmaconfig (struct a10codec_chinfo*) ; 
 int a10codec_fs (struct a10codec_chinfo*) ; 
 int /*<<< orphan*/  a10codec_transfer (struct a10codec_chinfo*) ; 
 int /*<<< orphan*/  stub1 (struct a10codec_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct a10codec_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
a10codec_start(struct a10codec_chinfo *ch)
{
	struct a10codec_info *sc = ch->parent;
	uint32_t val;

	ch->pos = 0;

	if (ch->dir == PCMDIR_PLAY) {
		/* Flush DAC FIFO */
		CODEC_WRITE(sc, AC_DAC_FIFOC(sc), DAC_FIFOC_FIFO_FLUSH);

		/* Clear DAC FIFO status */
		CODEC_WRITE(sc, AC_DAC_FIFOS(sc),
		    CODEC_READ(sc, AC_DAC_FIFOS(sc)));

		/* Unmute output */
		sc->cfg->mute(sc, 0, ch->dir);

		/* Configure DAC DMA channel */
		a10codec_dmaconfig(ch);

		/* Configure DAC FIFO */
		CODEC_WRITE(sc, AC_DAC_FIFOC(sc),
		    (AFMT_CHANNEL(ch->format) == 1 ? DAC_FIFOC_MONO_EN : 0) |
		    (a10codec_fs(ch) << DAC_FIFOC_FS_SHIFT) |
		    (FIFO_MODE_16_15_0 << DAC_FIFOC_FIFO_MODE_SHIFT) |
		    (DRQ_CLR_CNT << DAC_FIFOC_DRQ_CLR_CNT_SHIFT) |
		    (TX_TRIG_LEVEL << DAC_FIFOC_TX_TRIG_LEVEL_SHIFT));

		/* Enable DAC DRQ */
		val = CODEC_READ(sc, AC_DAC_FIFOC(sc));
		val |= DAC_FIFOC_DRQ_EN;
		CODEC_WRITE(sc, AC_DAC_FIFOC(sc), val);
	} else {
		/* Flush ADC FIFO */
		CODEC_WRITE(sc, AC_ADC_FIFOC(sc), ADC_FIFOC_FIFO_FLUSH);

		/* Clear ADC FIFO status */
		CODEC_WRITE(sc, AC_ADC_FIFOS(sc),
		    CODEC_READ(sc, AC_ADC_FIFOS(sc)));

		/* Unmute input */
		sc->cfg->mute(sc, 0, ch->dir);

		/* Configure ADC DMA channel */
		a10codec_dmaconfig(ch);

		/* Configure ADC FIFO */
		CODEC_WRITE(sc, AC_ADC_FIFOC(sc),
		    ADC_FIFOC_EN_AD |
		    ADC_FIFOC_RX_FIFO_MODE |
		    (AFMT_CHANNEL(ch->format) == 1 ? ADC_FIFOC_MONO_EN : 0) |
		    (a10codec_fs(ch) << ADC_FIFOC_FS_SHIFT) |
		    (RX_TRIG_LEVEL << ADC_FIFOC_RX_TRIG_LEVEL_SHIFT));

		/* Enable ADC DRQ */
		val = CODEC_READ(sc, AC_ADC_FIFOC(sc));
		val |= ADC_FIFOC_DRQ_EN;
		CODEC_WRITE(sc, AC_ADC_FIFOC(sc), val);
	}

	/* Start DMA transfer */
	a10codec_transfer(ch);
}