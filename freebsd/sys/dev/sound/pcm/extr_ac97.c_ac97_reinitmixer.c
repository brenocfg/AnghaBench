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
struct ac97_info {scalar_t__ count; int flags; int extstat; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  noext; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int AC97_EXTCAPS ; 
 int AC97_F_EAPD_INV ; 
 scalar_t__ AC97_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AC97_REGEXT_STAT ; 
 int /*<<< orphan*/  AC97_REG_POWER ; 
 int ENODEV ; 
 int ac97_rdcd (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_reset (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
ac97_reinitmixer(struct ac97_info *codec)
{
	snd_mtxlock(codec->lock);
	codec->count = AC97_INIT(codec->methods, codec->devinfo);
	if (codec->count == 0) {
		device_printf(codec->dev, "ac97 codec init failed\n");
		snd_mtxunlock(codec->lock);
		return ENODEV;
	}

	ac97_wrcd(codec, AC97_REG_POWER, (codec->flags & AC97_F_EAPD_INV)? 0x8000 : 0x0000);
	ac97_reset(codec);
	ac97_wrcd(codec, AC97_REG_POWER, (codec->flags & AC97_F_EAPD_INV)? 0x8000 : 0x0000);

	if (!codec->noext) {
		ac97_wrcd(codec, AC97_REGEXT_STAT, codec->extstat);
		if ((ac97_rdcd(codec, AC97_REGEXT_STAT) & AC97_EXTCAPS)
		    != codec->extstat)
			device_printf(codec->dev, "ac97 codec failed to reset extended mode (%x, got %x)\n",
				      codec->extstat,
				      ac97_rdcd(codec, AC97_REGEXT_STAT) &
				      AC97_EXTCAPS);
	}

	if ((ac97_rdcd(codec, AC97_REG_POWER) & 2) == 0)
		device_printf(codec->dev, "ac97 codec reports dac not ready\n");
	snd_mtxunlock(codec->lock);
	return 0;
}