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
typedef  int u_int32_t ;
struct snd_mixer {int dummy; } ;
struct sc_info {int dummy; } ;
struct TYPE_2__ {int iselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int SOUND_MIXER_NRDEVICES ; 
 int SV_INPUT_GAIN_MASK ; 
 int /*<<< orphan*/  SV_REG_ADC_INPUT ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 
 TYPE_1__* mt ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int sv_indirect_get (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_indirect_set (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
sv_mix_setrecsrc(struct snd_mixer *m, u_int32_t mask)
{
	struct sc_info	*sc = mix_getdevinfo(m);
	u_int32_t	i, v;

	v = sv_indirect_get(sc, SV_REG_ADC_INPUT) & SV_INPUT_GAIN_MASK;
	for(i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if ((1 << i) & mask) {
			v |= mt[i].iselect;
		}
	}
	DEB(printf("sv_mix_setrecsrc: mask 0x%08x adc_input 0x%02x\n", mask, v));
	sv_indirect_set(sc, SV_REG_ADC_INPUT, v);
	return mask;
}