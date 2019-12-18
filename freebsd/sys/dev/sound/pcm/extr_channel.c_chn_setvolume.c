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
 int /*<<< orphan*/  SND_CHN_T_FL ; 
 int /*<<< orphan*/  SND_CHN_T_FR ; 
 int /*<<< orphan*/  SND_VOL_C_MASTER ; 
 int chn_setvolume_matrix (struct pcm_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
chn_setvolume(struct pcm_channel *c, int left, int right)
{
	int ret;

	ret = chn_setvolume_matrix(c, SND_VOL_C_MASTER, SND_CHN_T_FL, left);
	ret |= chn_setvolume_matrix(c, SND_VOL_C_MASTER, SND_CHN_T_FR,
	    right) << 8;

	return (ret);
}