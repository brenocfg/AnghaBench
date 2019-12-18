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
struct ac97mixtable_entry {int recidx; } ;
struct ac97_info {int /*<<< orphan*/  lock; struct ac97mixtable_entry* mix; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_REG_RECSEL ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ac97_setrecsrc(struct ac97_info *codec, int channel)
{
	struct ac97mixtable_entry *e = &codec->mix[channel];

	if (e->recidx > 0) {
		int val = e->recidx - 1;
		val |= val << 8;
		snd_mtxlock(codec->lock);
		ac97_wrcd(codec, AC97_REG_RECSEL, val);
		snd_mtxunlock(codec->lock);
		return 0;
	} else
		return -1;
}