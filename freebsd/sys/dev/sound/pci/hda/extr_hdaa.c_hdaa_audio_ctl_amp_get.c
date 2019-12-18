#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdaa_devinfo {int /*<<< orphan*/ * ctl; } ;
struct hdaa_audio_ctl {scalar_t__ enable; int ndir; int dir; int index; TYPE_1__* widget; } ;
typedef  scalar_t__ nid_t ;
struct TYPE_2__ {scalar_t__ nid; } ;

/* Variables and functions */
 int HDAA_CTL_IN ; 
 struct hdaa_audio_ctl* hdaa_audio_ctl_each (struct hdaa_devinfo*,int*) ; 

__attribute__((used)) static struct hdaa_audio_ctl *
hdaa_audio_ctl_amp_get(struct hdaa_devinfo *devinfo, nid_t nid, int dir,
						int index, int cnt)
{
	struct hdaa_audio_ctl *ctl;
	int i, found = 0;

	if (devinfo == NULL || devinfo->ctl == NULL)
		return (NULL);

	i = 0;
	while ((ctl = hdaa_audio_ctl_each(devinfo, &i)) != NULL) {
		if (ctl->enable == 0)
			continue;
		if (ctl->widget->nid != nid)
			continue;
		if (dir && ctl->ndir != dir)
			continue;
		if (index >= 0 && ctl->ndir == HDAA_CTL_IN &&
		    ctl->dir == ctl->ndir && ctl->index != index)
			continue;
		found++;
		if (found == cnt || cnt <= 0)
			return (ctl);
	}

	return (NULL);
}