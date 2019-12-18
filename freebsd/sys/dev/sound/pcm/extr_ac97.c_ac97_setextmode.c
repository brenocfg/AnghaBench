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
typedef  int u_int16_t ;
struct ac97_info {int extcaps; int extstat; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC97_EXTCAPS ; 
 int /*<<< orphan*/  AC97_REGEXT_STAT ; 
 int ac97_rdcd (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

int
ac97_setextmode(struct ac97_info *codec, u_int16_t mode)
{
	mode &= AC97_EXTCAPS;
	if ((mode & ~codec->extcaps) != 0) {
		device_printf(codec->dev, "ac97 invalid mode set 0x%04x\n",
			      mode);
		return -1;
	}
	snd_mtxlock(codec->lock);
	ac97_wrcd(codec, AC97_REGEXT_STAT, mode);
	codec->extstat = ac97_rdcd(codec, AC97_REGEXT_STAT) & AC97_EXTCAPS;
	snd_mtxunlock(codec->lock);
	return (mode == codec->extstat)? 0 : -1;
}