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
struct mss_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPL3SAx_BASS ; 
 int /*<<< orphan*/  OPL3SAx_MIC ; 
 int /*<<< orphan*/  OPL3SAx_TREBLE ; 
 int /*<<< orphan*/  OPL3SAx_VOLUMEL ; 
 int /*<<< orphan*/  OPL3SAx_VOLUMER ; 
#define  SOUND_MIXER_BASS 131 
#define  SOUND_MIXER_MIC 130 
#define  SOUND_MIXER_TREBLE 129 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  conf_wr (struct mss_info*,int /*<<< orphan*/ ,int) ; 
 struct mss_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_mixer_set (struct mss_info*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 

__attribute__((used)) static int
ymmix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct mss_info *mss = mix_getdevinfo(m);
	int t, l, r;

	mss_lock(mss);
	switch (dev) {
	case SOUND_MIXER_VOLUME:
		if (left) t = 15 - (left * 15) / 100;
		else t = 0x80; /* mute */
		conf_wr(mss, OPL3SAx_VOLUMEL, t);
		if (right) t = 15 - (right * 15) / 100;
		else t = 0x80; /* mute */
		conf_wr(mss, OPL3SAx_VOLUMER, t);
		break;

	case SOUND_MIXER_MIC:
		t = left;
		if (left) t = 31 - (left * 31) / 100;
		else t = 0x80; /* mute */
		conf_wr(mss, OPL3SAx_MIC, t);
		break;

	case SOUND_MIXER_BASS:
		l = (left * 7) / 100;
		r = (right * 7) / 100;
		t = (r << 4) | l;
		conf_wr(mss, OPL3SAx_BASS, t);
		break;

	case SOUND_MIXER_TREBLE:
		l = (left * 7) / 100;
		r = (right * 7) / 100;
		t = (r << 4) | l;
		conf_wr(mss, OPL3SAx_TREBLE, t);
		break;

	default:
		mss_mixer_set(mss, dev, left, right);
	}
	mss_unlock(mss);

	return left | (right << 8);
}