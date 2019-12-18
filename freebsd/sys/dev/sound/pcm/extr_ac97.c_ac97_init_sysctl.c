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
struct ac97_info {int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  codec ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_REG_POWER ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ac97_info*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int ac97_rdcd (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_hw_snd_ac97_eapd ; 

__attribute__((used)) static void
ac97_init_sysctl(struct ac97_info *codec)
{
	u_int16_t orig, val;

	if (codec == NULL || codec->dev == NULL)
		return;
	snd_mtxlock(codec->lock);
	orig = ac97_rdcd(codec, AC97_REG_POWER);
	ac97_wrcd(codec, AC97_REG_POWER, orig ^ 0x8000);
	val = ac97_rdcd(codec, AC97_REG_POWER);
	ac97_wrcd(codec, AC97_REG_POWER, orig);
	snd_mtxunlock(codec->lock);
	if ((val & 0x8000) == (orig & 0x8000))
		return;
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(codec->dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(codec->dev)),
            OID_AUTO, "eapd", CTLTYPE_INT | CTLFLAG_RW,
	    codec, sizeof(codec), sysctl_hw_snd_ac97_eapd,
	    "I", "AC97 External Amplifier");
}