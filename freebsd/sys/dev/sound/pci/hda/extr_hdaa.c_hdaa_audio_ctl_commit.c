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
struct hdaa_devinfo {int dummy; } ;
struct hdaa_audio_ctl {scalar_t__ enable; scalar_t__ ossmask; int offset; int step; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDAA_AMP_MUTE_ALL ; 
 int /*<<< orphan*/  HDAA_AMP_MUTE_NONE ; 
 int /*<<< orphan*/  hdaa_audio_ctl_amp_set (struct hdaa_audio_ctl*,int /*<<< orphan*/ ,int,int) ; 
 struct hdaa_audio_ctl* hdaa_audio_ctl_each (struct hdaa_devinfo*,int*) ; 

__attribute__((used)) static void
hdaa_audio_ctl_commit(struct hdaa_devinfo *devinfo)
{
	struct hdaa_audio_ctl *ctl;
	int i, z;

	i = 0;
	while ((ctl = hdaa_audio_ctl_each(devinfo, &i)) != NULL) {
		if (ctl->enable == 0 || ctl->ossmask != 0) {
			/* Mute disabled and mixer controllable controls.
			 * Last will be initialized by mixer_init().
			 * This expected to reduce click on startup. */
			hdaa_audio_ctl_amp_set(ctl, HDAA_AMP_MUTE_ALL, 0, 0);
			continue;
		}
		/* Init fixed controls to 0dB amplification. */
		z = ctl->offset;
		if (z > ctl->step)
			z = ctl->step;
		hdaa_audio_ctl_amp_set(ctl, HDAA_AMP_MUTE_NONE, z, z);
	}
}