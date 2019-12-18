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
struct hdaa_devinfo {int ctlcnt; struct hdaa_audio_ctl* ctl; } ;
struct hdaa_audio_ctl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct hdaa_audio_ctl *
hdaa_audio_ctl_each(struct hdaa_devinfo *devinfo, int *index)
{
	if (devinfo == NULL ||
	    index == NULL || devinfo->ctl == NULL ||
	    devinfo->ctlcnt < 1 ||
	    *index < 0 || *index >= devinfo->ctlcnt)
		return (NULL);
	return (&devinfo->ctl[(*index)++]);
}