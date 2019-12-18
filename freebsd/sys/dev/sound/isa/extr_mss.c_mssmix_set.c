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
 struct mss_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_mixer_set (struct mss_info*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 

__attribute__((used)) static int
mssmix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct mss_info *mss = mix_getdevinfo(m);

	mss_lock(mss);
	mss_mixer_set(mss, dev, left, right);
	mss_unlock(mss);

	return left | (right << 8);
}