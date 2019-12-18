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
struct mss_info {int bd_id; } ;

/* Variables and functions */
#define  MD_AD1848 132 
#define  MD_GUSMAX 131 
#define  MD_GUSPNP 130 
#define  MD_OPTI930 129 
#define  MD_OPTI931 128 
 int /*<<< orphan*/  MODE1_MIXER_DEVICES ; 
 int /*<<< orphan*/  MODE2_MIXER_DEVICES ; 
 int /*<<< orphan*/  MSS_REC_DEVICES ; 
 int /*<<< orphan*/  OPTI930_MIXER_DEVICES ; 
 int /*<<< orphan*/  OPTI931_MIXER_DEVICES ; 
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 
 struct mss_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 

__attribute__((used)) static int
mssmix_init(struct snd_mixer *m)
{
	struct mss_info *mss = mix_getdevinfo(m);

	mix_setdevs(m, MODE2_MIXER_DEVICES);
	mix_setrecdevs(m, MSS_REC_DEVICES);
	switch(mss->bd_id) {
	case MD_OPTI930:
		mix_setdevs(m, OPTI930_MIXER_DEVICES);
		break;

	case MD_OPTI931:
		mix_setdevs(m, OPTI931_MIXER_DEVICES);
		mss_lock(mss);
		ad_write(mss, 20, 0x88);
		ad_write(mss, 21, 0x88);
		mss_unlock(mss);
		break;

	case MD_AD1848:
		mix_setdevs(m, MODE1_MIXER_DEVICES);
		break;

	case MD_GUSPNP:
	case MD_GUSMAX:
		/* this is only necessary in mode 3 ... */
		mss_lock(mss);
		ad_write(mss, 22, 0x88);
		ad_write(mss, 23, 0x88);
		mss_unlock(mss);
		break;
	}
	return 0;
}