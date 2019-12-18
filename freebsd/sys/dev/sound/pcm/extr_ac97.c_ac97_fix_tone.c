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
struct ac97_info {int id; int caps; int se; int /*<<< orphan*/ * mix; } ;

/* Variables and functions */
 int AC97_CAP_TONE ; 
 size_t SOUND_MIXER_BASS ; 
 size_t SOUND_MIXER_TREBLE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ac97_fix_tone(struct ac97_info *codec)
{
	/*
	 * YMF chips does not indicate tone and 3D enhancement capability
	 * in the AC97_REG_RESET register.
	 */
	switch (codec->id) {
	case 0x594d4800:	/* YMF743 */
	case 0x594d4803:	/* YMF753 */
		codec->caps |= AC97_CAP_TONE;
		codec->se |= 0x04;
		break;
	case 0x594d4802:	/* YMF752 */
		codec->se |= 0x04;
		break;
	default:
		break;
	}

	/* Hide treble and bass if they don't exist */
	if ((codec->caps & AC97_CAP_TONE) == 0) {
		bzero(&codec->mix[SOUND_MIXER_BASS],
		      sizeof(codec->mix[SOUND_MIXER_BASS]));
		bzero(&codec->mix[SOUND_MIXER_TREBLE],
		      sizeof(codec->mix[SOUND_MIXER_TREBLE]));
	}
}