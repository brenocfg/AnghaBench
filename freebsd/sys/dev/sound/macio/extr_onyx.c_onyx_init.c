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
typedef  int /*<<< orphan*/  u_int ;
struct snd_mixer {int dummy; } ;
struct onyx_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  INFO_4; int /*<<< orphan*/  INFO_3; int /*<<< orphan*/  INFO_2; int /*<<< orphan*/  INFO_1; int /*<<< orphan*/  ADC_HPF_BP; int /*<<< orphan*/  ADC_CONTROL; int /*<<< orphan*/  OUT_PHASE; int /*<<< orphan*/  DAC_FILTER; int /*<<< orphan*/  DAC_DEEMPH; int /*<<< orphan*/  DAC_CONTROL; int /*<<< orphan*/  CONTROL; int /*<<< orphan*/  RIGHT_ATTN; int /*<<< orphan*/  LEFT_ATTN; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM3052_REG_ADC_CONTROL ; 
 int /*<<< orphan*/  PCM3052_REG_ADC_HPF_BP ; 
 int /*<<< orphan*/  PCM3052_REG_CONTROL ; 
 int /*<<< orphan*/  PCM3052_REG_DAC_CONTROL ; 
 int /*<<< orphan*/  PCM3052_REG_DAC_DEEMPH ; 
 int /*<<< orphan*/  PCM3052_REG_DAC_FILTER ; 
 int /*<<< orphan*/  PCM3052_REG_INFO_1 ; 
 int /*<<< orphan*/  PCM3052_REG_INFO_2 ; 
 int /*<<< orphan*/  PCM3052_REG_INFO_3 ; 
 int /*<<< orphan*/  PCM3052_REG_INFO_4 ; 
 int /*<<< orphan*/  PCM3052_REG_LEFT_ATTN ; 
 int /*<<< orphan*/  PCM3052_REG_OUT_PHASE ; 
 int /*<<< orphan*/  PCM3052_REG_RIGHT_ATTN ; 
 int /*<<< orphan*/  SOUND_MASK_VOLUME ; 
 struct onyx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 TYPE_1__ onyx_initdata ; 
 int /*<<< orphan*/  onyx_write (struct onyx_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
onyx_init(struct snd_mixer *m)
{
	struct onyx_softc *sc;
	u_int  x = 0;

	sc = device_get_softc(mix_getdevinfo(m));

	onyx_write(sc, PCM3052_REG_LEFT_ATTN, onyx_initdata.LEFT_ATTN);
	onyx_write(sc, PCM3052_REG_RIGHT_ATTN, onyx_initdata.RIGHT_ATTN);
	onyx_write(sc, PCM3052_REG_CONTROL, onyx_initdata.CONTROL);
	onyx_write(sc, PCM3052_REG_DAC_CONTROL,
		      onyx_initdata.DAC_CONTROL);
	onyx_write(sc, PCM3052_REG_DAC_DEEMPH, onyx_initdata.DAC_DEEMPH);
	onyx_write(sc, PCM3052_REG_DAC_FILTER, onyx_initdata.DAC_FILTER);
	onyx_write(sc, PCM3052_REG_OUT_PHASE, onyx_initdata.OUT_PHASE);
	onyx_write(sc, PCM3052_REG_ADC_CONTROL,
		      onyx_initdata.ADC_CONTROL);
	onyx_write(sc, PCM3052_REG_ADC_HPF_BP, onyx_initdata.ADC_HPF_BP);
	onyx_write(sc, PCM3052_REG_INFO_1, onyx_initdata.INFO_1);
	onyx_write(sc, PCM3052_REG_INFO_2, onyx_initdata.INFO_2);
	onyx_write(sc, PCM3052_REG_INFO_3, onyx_initdata.INFO_3);
	onyx_write(sc, PCM3052_REG_INFO_4, onyx_initdata.INFO_4);

	x |= SOUND_MASK_VOLUME;
	mix_setdevs(m, x);

	return (0);
}