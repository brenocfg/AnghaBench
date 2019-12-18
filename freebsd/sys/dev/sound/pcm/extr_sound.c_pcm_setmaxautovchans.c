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
struct snddev_info {int pvchancount; int rvchancount; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  pcm_clonereset (struct snddev_info*) ; 
 int /*<<< orphan*/  pcm_setvchans (struct snddev_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
pcm_setmaxautovchans(struct snddev_info *d, int num)
{
	PCM_BUSYASSERT(d);

	if (num < 0)
		return;

	if (num >= 0 && d->pvchancount > num)
		(void)pcm_setvchans(d, PCMDIR_PLAY, num, -1);
	else if (num > 0 && d->pvchancount == 0)
		(void)pcm_setvchans(d, PCMDIR_PLAY, 1, -1);

	if (num >= 0 && d->rvchancount > num)
		(void)pcm_setvchans(d, PCMDIR_REC, num, -1);
	else if (num > 0 && d->rvchancount == 0)
		(void)pcm_setvchans(d, PCMDIR_REC, 1, -1);

	pcm_clonereset(d);
}