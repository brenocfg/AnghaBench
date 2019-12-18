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
 int /*<<< orphan*/  OPL3SAx_VOLUMEL ; 
 int /*<<< orphan*/  OPL3SAx_VOLUMER ; 
 int SOUND_MASK_BASS ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_TREBLE ; 
 int SOUND_MASK_VOLUME ; 
 int /*<<< orphan*/  conf_wr (struct mss_info*,int /*<<< orphan*/ ,int) ; 
 struct mss_info* mix_getdevinfo (struct snd_mixer*) ; 
 int mix_getdevs (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 
 int /*<<< orphan*/  mssmix_init (struct snd_mixer*) ; 

__attribute__((used)) static int
ymmix_init(struct snd_mixer *m)
{
	struct mss_info *mss = mix_getdevinfo(m);

	mssmix_init(m);
	mix_setdevs(m, mix_getdevs(m) | SOUND_MASK_VOLUME | SOUND_MASK_MIC
				      | SOUND_MASK_BASS | SOUND_MASK_TREBLE);
	/* Set master volume */
	mss_lock(mss);
	conf_wr(mss, OPL3SAx_VOLUMEL, 7);
	conf_wr(mss, OPL3SAx_VOLUMER, 7);
	mss_unlock(mss);

	return 0;
}