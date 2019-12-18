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
struct pcm_channel {int flags; } ;

/* Variables and functions */
 int CHN_F_BITPERFECT ; 
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int EINVAL ; 

__attribute__((used)) static int
dsp_oss_cookedmode(struct pcm_channel *wrch, struct pcm_channel *rdch, int enabled)
{

	/*
	 * XXX I just don't get it. Why don't they call it
	 * "BITPERFECT" ~ SNDCTL_DSP_BITPERFECT !?!?.
	 * This is just plain so confusing, incoherent,
	 * <insert any non-printable characters here>.
	 */
	if (!(enabled == 1 || enabled == 0))
		return (EINVAL);

	/*
	 * I won't give in. I'm inverting its logic here and now.
	 * Brag all you want, but "BITPERFECT" should be the better
	 * term here.
	 */
	enabled ^= 0x00000001;

	if (wrch != NULL) {
		CHN_LOCK(wrch);
		wrch->flags &= ~CHN_F_BITPERFECT;
		wrch->flags |= (enabled != 0) ? CHN_F_BITPERFECT : 0x00000000;
		CHN_UNLOCK(wrch);
	}

	if (rdch != NULL) {
		CHN_LOCK(rdch);
		rdch->flags &= ~CHN_F_BITPERFECT;
		rdch->flags |= (enabled != 0) ? CHN_F_BITPERFECT : 0x00000000;
		CHN_UNLOCK(rdch);
	}

	return (0);
}