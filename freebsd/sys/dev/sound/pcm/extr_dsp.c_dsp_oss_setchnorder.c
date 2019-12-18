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
struct pcm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int chn_oss_setorder (struct pcm_channel*,unsigned long long*) ; 

__attribute__((used)) static int
dsp_oss_setchnorder(struct pcm_channel *wrch, struct pcm_channel *rdch, unsigned long long *map)
{
	int ret;

	ret = 0;

	if (wrch != NULL) {
		CHN_LOCK(wrch);
		ret = chn_oss_setorder(wrch, map);
		CHN_UNLOCK(wrch);
	}

	if (ret == 0 && rdch != NULL) {
		CHN_LOCK(rdch);
		ret = chn_oss_setorder(rdch, map);
		CHN_UNLOCK(rdch);
	}

	return (ret);
}