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
typedef  int uint32_t ;
struct pcm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int EINVAL ; 
 int chn_oss_getmask (struct pcm_channel*,int*) ; 

__attribute__((used)) static int
dsp_oss_getchannelmask(struct pcm_channel *wrch, struct pcm_channel *rdch,
    int *mask)
{
	struct pcm_channel *ch;
	uint32_t chnmask;
	int ret;

	chnmask = 0;
	ch = (wrch != NULL) ? wrch : rdch;

	if (ch != NULL) {
		CHN_LOCK(ch);
		ret = chn_oss_getmask(ch, &chnmask);
		CHN_UNLOCK(ch);
	} else
		ret = EINVAL;

	if (ret == 0)
		*mask = chnmask;

	return (ret);
}