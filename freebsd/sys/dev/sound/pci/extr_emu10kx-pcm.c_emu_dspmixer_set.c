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
struct snd_mixer {int dummy; } ;
struct emu_pcm_info {unsigned int** emu10k1_volcache; int /*<<< orphan*/  dev; int /*<<< orphan*/ * sm; int /*<<< orphan*/  card; int /*<<< orphan*/  is_emu10k1; int /*<<< orphan*/  mch_disabled; int /*<<< orphan*/  route; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FX2_REAR_L ; 
 int /*<<< orphan*/  M_FX3_REAR_R ; 
 int /*<<< orphan*/  M_FX4_CENTER ; 
 int /*<<< orphan*/  M_FX5_SUBWOOFER ; 
 int /*<<< orphan*/  M_IN0_FRONT_L ; 
 int /*<<< orphan*/  M_IN0_FRONT_R ; 
 int /*<<< orphan*/  M_IN1_FRONT_L ; 
 int /*<<< orphan*/  M_IN1_FRONT_R ; 
 int /*<<< orphan*/  M_IN2_FRONT_L ; 
 int /*<<< orphan*/  M_IN2_FRONT_R ; 
 int /*<<< orphan*/  M_IN3_FRONT_L ; 
 int /*<<< orphan*/  M_IN3_FRONT_R ; 
 int /*<<< orphan*/  M_IN4_FRONT_L ; 
 int /*<<< orphan*/  M_IN4_FRONT_R ; 
 int /*<<< orphan*/  M_IN5_FRONT_L ; 
 int /*<<< orphan*/  M_IN5_FRONT_R ; 
 int /*<<< orphan*/  M_IN6_FRONT_L ; 
 int /*<<< orphan*/  M_IN6_FRONT_R ; 
 int /*<<< orphan*/  M_MASTER_CENTER ; 
 int /*<<< orphan*/  M_MASTER_REAR_L ; 
 int /*<<< orphan*/  M_MASTER_REAR_R ; 
 int /*<<< orphan*/  M_MASTER_SUBWOOFER ; 
#define  RT_CENTER 138 
#define  RT_FRONT 137 
#define  RT_REAR 136 
#define  RT_SUB 135 
#define  SOUND_MIXER_DIGITAL1 134 
#define  SOUND_MIXER_DIGITAL2 133 
#define  SOUND_MIXER_DIGITAL3 132 
#define  SOUND_MIXER_LINE2 131 
#define  SOUND_MIXER_LINE3 130 
#define  SOUND_MIXER_PCM 129 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  emumix_set_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct emu_pcm_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_set (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
emu_dspmixer_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct emu_pcm_info *sc;

	sc = mix_getdevinfo(m);

	switch (dev) {
	case SOUND_MIXER_VOLUME:
		switch (sc->route) {
		case RT_FRONT:
			if (sc->sm != NULL)
				mix_set(sc->sm, dev, left, right);
			if (sc->mch_disabled) {
				/* In emu10k1 case PCM volume does not affect
				   sound routed to rear & center/sub (it is connected
				   to AC97 codec). Calculate it manually. */
				/* This really should belong to emu10kx.c */
				if (sc->is_emu10k1) {
					sc->emu10k1_volcache[0][0] = left;
					left = left * sc->emu10k1_volcache[1][0] / 100;
					sc->emu10k1_volcache[0][1] = right;
					right = right * sc->emu10k1_volcache[1][1] / 100;
				}

				emumix_set_volume(sc->card, M_MASTER_REAR_L, left);
				emumix_set_volume(sc->card, M_MASTER_REAR_R, right);
				if (!sc->is_emu10k1) {
					emumix_set_volume(sc->card, M_MASTER_CENTER, (left+right)/2);
					emumix_set_volume(sc->card, M_MASTER_SUBWOOFER, (left+right)/2);
					/* XXX side */
				}
			} /* mch disabled */
			break;
		case RT_REAR:
			emumix_set_volume(sc->card, M_MASTER_REAR_L, left);
			emumix_set_volume(sc->card, M_MASTER_REAR_R, right);
			break;
		case RT_CENTER:
			emumix_set_volume(sc->card, M_MASTER_CENTER, (left+right)/2);
			break;
		case RT_SUB:
			emumix_set_volume(sc->card, M_MASTER_SUBWOOFER, (left+right)/2);
			break;
		}
		break;
	case SOUND_MIXER_PCM:
		switch (sc->route) {
		case RT_FRONT:
			if (sc->sm != NULL)
				mix_set(sc->sm, dev, left, right);
			if (sc->mch_disabled) {
				/* See SOUND_MIXER_VOLUME case */
				if (sc->is_emu10k1) {
					sc->emu10k1_volcache[1][0] = left;
					left = left * sc->emu10k1_volcache[0][0] / 100;
					sc->emu10k1_volcache[1][1] = right;
					right = right * sc->emu10k1_volcache[0][1] / 100;
				}
				emumix_set_volume(sc->card, M_MASTER_REAR_L, left);
				emumix_set_volume(sc->card, M_MASTER_REAR_R, right);

				if (!sc->is_emu10k1) {
					emumix_set_volume(sc->card, M_MASTER_CENTER, (left+right)/2);
					emumix_set_volume(sc->card, M_MASTER_SUBWOOFER, (left+right)/2);
					/* XXX side */
				}
			} /* mch_disabled */
			break;
		case RT_REAR:
			emumix_set_volume(sc->card, M_FX2_REAR_L, left);
			emumix_set_volume(sc->card, M_FX3_REAR_R, right);
			break;
		case RT_CENTER:
			emumix_set_volume(sc->card, M_FX4_CENTER, (left+right)/2);
			break;
		case RT_SUB:
			emumix_set_volume(sc->card, M_FX5_SUBWOOFER, (left+right)/2);
			break;
		}
		break;
	case SOUND_MIXER_DIGITAL1:	/* CD SPDIF, in1 */
			emumix_set_volume(sc->card, M_IN1_FRONT_L, left);
			emumix_set_volume(sc->card, M_IN1_FRONT_R, right);
		break;
	case SOUND_MIXER_DIGITAL2:
			if (sc->is_emu10k1) {
				/* TOSLink, in3 */
				emumix_set_volume(sc->card, M_IN3_FRONT_L, left);
				emumix_set_volume(sc->card, M_IN3_FRONT_R, right);
			} else {
				/* COAX SPDIF, in2 */
				emumix_set_volume(sc->card, M_IN2_FRONT_L, left);
				emumix_set_volume(sc->card, M_IN2_FRONT_R, right);
			}
		break;
	case SOUND_MIXER_LINE2:		/* Line-In2, in4 */
			emumix_set_volume(sc->card, M_IN4_FRONT_L, left);
			emumix_set_volume(sc->card, M_IN4_FRONT_R, right);
		break;
	case SOUND_MIXER_DIGITAL3:	/* on-card SPDIF, in5 */
			emumix_set_volume(sc->card, M_IN5_FRONT_L, left);
			emumix_set_volume(sc->card, M_IN5_FRONT_R, right);
		break;
	case SOUND_MIXER_LINE3:		/* AUX2, in6 */
			emumix_set_volume(sc->card, M_IN6_FRONT_L, left);
			emumix_set_volume(sc->card, M_IN6_FRONT_R, right);
		break;
	default:
		if (sc->sm != NULL) {
			/* XXX emumix_set_volume is not required here */
			emumix_set_volume(sc->card, M_IN0_FRONT_L, 100);
			emumix_set_volume(sc->card, M_IN0_FRONT_R, 100);
			mix_set(sc->sm, dev, left, right);
		} else
			device_printf(sc->dev, "mixer error: unknown device %d\n", dev);
	}
	return  (0);
}