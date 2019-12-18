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
struct es_info {int ctrl; int sctrl; void* escfg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int minspeed; int maxspeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_ADSEL ; 
 int /*<<< orphan*/  CODEC_CSEL ; 
 int /*<<< orphan*/  CODEC_MGAIN ; 
 int /*<<< orphan*/  CODEC_RES_PD ; 
 int CTRL_CDC_EN ; 
 int CTRL_JYSTK_EN ; 
 int CTRL_SERR_DIS ; 
 int CTRL_SH_PCLKDIV ; 
 int CTRL_SH_WTSRSEL ; 
 int DAC2_SRTODIV (int) ; 
 int DSP_DEFAULT_SPEED ; 
 int /*<<< orphan*/  ES1370_REG_CONTROL ; 
 int /*<<< orphan*/  ES1370_REG_SERIAL_CONTROL ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int ES_NUMPLAY (void*) ; 
 void* ES_SET_FIXED_RATE (void*,int) ; 
 void* ES_SET_IS_ES1370 (void*,int) ; 
 void* ES_SET_SINGLE_PCM_MIX (void*,int) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es1370_wrcodec (struct es_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ es_caps ; 
 int /*<<< orphan*/  es_wr (struct es_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
es1370_init(struct es_info *es)
{
	uint32_t fixed_rate;
	int r, single_pcm;

	/* ES1370 default to fixed rate operation */
	if (resource_int_value(device_get_name(es->dev),
	    device_get_unit(es->dev), "fixed_rate", &r) == 0) {
		fixed_rate = r;
		if (fixed_rate) {
			if (fixed_rate < es_caps.minspeed)
				fixed_rate = es_caps.minspeed;
			if (fixed_rate > es_caps.maxspeed)
				fixed_rate = es_caps.maxspeed;
		}
	} else
		fixed_rate = es_caps.maxspeed;

	if (resource_int_value(device_get_name(es->dev),
	    device_get_unit(es->dev), "single_pcm_mixer", &r) == 0)
		single_pcm = (r != 0) ? 1 : 0;
	else
		single_pcm = 1;

	ES_LOCK(es);
	if (ES_NUMPLAY(es->escfg) == 1)
		single_pcm = 1;
	/* This is ES1370 */
	es->escfg = ES_SET_IS_ES1370(es->escfg, 1);
	if (fixed_rate)
		es->escfg = ES_SET_FIXED_RATE(es->escfg, fixed_rate);
	else {
		es->escfg = ES_SET_FIXED_RATE(es->escfg, 0);
		fixed_rate = DSP_DEFAULT_SPEED;
	}
	if (single_pcm)
		es->escfg = ES_SET_SINGLE_PCM_MIX(es->escfg, 1);
	else
		es->escfg = ES_SET_SINGLE_PCM_MIX(es->escfg, 0);
	es->ctrl = CTRL_CDC_EN | CTRL_JYSTK_EN | CTRL_SERR_DIS |
	    (DAC2_SRTODIV(fixed_rate) << CTRL_SH_PCLKDIV);
	es->ctrl |= 3 << CTRL_SH_WTSRSEL;
	es_wr(es, ES1370_REG_CONTROL, es->ctrl, 4);

	es->sctrl = 0;
	es_wr(es, ES1370_REG_SERIAL_CONTROL, es->sctrl, 4);

	/* No RST, PD */
	es1370_wrcodec(es, CODEC_RES_PD, 3);
	/*
	 * CODEC ADC and CODEC DAC use {LR,B}CLK2 and run off the LRCLK2 PLL;
	 * program DAC_SYNC=0!
	 */
	es1370_wrcodec(es, CODEC_CSEL, 0);
	/* Recording source is mixer */
	es1370_wrcodec(es, CODEC_ADSEL, 0);
	/* MIC amp is 0db */
	es1370_wrcodec(es, CODEC_MGAIN, 0);
	ES_UNLOCK(es);

	return (0);
}