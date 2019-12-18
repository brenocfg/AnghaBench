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
typedef  int /*<<< orphan*/  u_int32_t ;
struct snd_mixer {int dummy; } ;
struct mss_info {int dummy; } ;

/* Variables and functions */
 struct mss_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_set_recsrc (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 

__attribute__((used)) static u_int32_t
mssmix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct mss_info *mss = mix_getdevinfo(m);

	mss_lock(mss);
	src = mss_set_recsrc(mss, src);
	mss_unlock(mss);
	return src;
}