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
struct TYPE_2__ {int iselect; scalar_t__ stereo; } ;

/* Variables and functions */
 int CMPCI_SB16_MIXER_ADCMIX_L ; 
 int CMPCI_SB16_MIXER_ADCMIX_R ; 
 int CMPCI_SB16_MIXER_SRC_R_TO_L (int) ; 
 int /*<<< orphan*/  DEBMIX (int /*<<< orphan*/ ) ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  cmimix_wr (struct sc_info*,int,int) ; 
 TYPE_1__* cmt ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static u_int32_t
cmimix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct sc_info *sc = mix_getdevinfo(m);
	u_int32_t i, ml, sl;

	ml = sl = 0;
	for(i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if ((1<<i) & src) {
			if (cmt[i].stereo) {
				sl |= cmt[i].iselect;
			} else {
				ml |= cmt[i].iselect;
			}
		}
	}
	cmimix_wr(sc, CMPCI_SB16_MIXER_ADCMIX_R, sl|ml);
	DEBMIX(printf("cmimix_setrecsrc: reg 0x%02x val 0x%02x\n",
		      CMPCI_SB16_MIXER_ADCMIX_R, sl|ml));
	ml = CMPCI_SB16_MIXER_SRC_R_TO_L(ml);
	cmimix_wr(sc, CMPCI_SB16_MIXER_ADCMIX_L, sl|ml);
	DEBMIX(printf("cmimix_setrecsrc: reg 0x%02x val 0x%02x\n",
		      CMPCI_SB16_MIXER_ADCMIX_L, sl|ml));

	return src;
}