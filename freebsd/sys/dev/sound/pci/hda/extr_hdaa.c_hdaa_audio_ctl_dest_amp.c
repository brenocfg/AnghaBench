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
struct hdaa_widget {scalar_t__ enable; int nconns; scalar_t__* connsenable; scalar_t__* conns; size_t bindas; int bindseqmask; scalar_t__ type; int /*<<< orphan*/  nid; } ;
struct hdaa_devinfo {int startnode; int endnode; struct hdaa_audio_as* as; } ;
struct hdaa_audio_ctl {int ossmask; } ;
struct hdaa_audio_as {scalar_t__ hpredir; scalar_t__ fakeredir; } ;
typedef  scalar_t__ nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAA_CTL_IN ; 
 int /*<<< orphan*/  HDAA_CTL_OUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 int HDA_PARSE_MAXDEPTH ; 
 scalar_t__ MAXQDB (struct hdaa_audio_ctl*) ; 
 scalar_t__ MINQDB (struct hdaa_audio_ctl*) ; 
 struct hdaa_audio_ctl* hdaa_audio_ctl_amp_get (struct hdaa_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 int imax (int,int) ; 
 int imin (int,int) ; 

__attribute__((used)) static int
hdaa_audio_ctl_dest_amp(struct hdaa_devinfo *devinfo, nid_t nid, int index,
    int ossdev, int depth, int *minamp, int *maxamp)
{
	struct hdaa_audio_as *as = devinfo->as;
	struct hdaa_widget *w, *wc;
	struct hdaa_audio_ctl *ctl;
	int i, j, consumers, tminamp, tmaxamp, cminamp, cmaxamp, found = 0;

	if (depth > HDA_PARSE_MAXDEPTH)
		return (found);

	w = hdaa_widget_get(devinfo, nid);
	if (w == NULL || w->enable == 0)
		return (found);

	if (depth > 0) {
		/* If this node produce output for several consumers,
		   we can't touch it. */
		consumers = 0;
		for (i = devinfo->startnode; i < devinfo->endnode; i++) {
			wc = hdaa_widget_get(devinfo, i);
			if (wc == NULL || wc->enable == 0)
				continue;
			for (j = 0; j < wc->nconns; j++) {
				if (wc->connsenable[j] && wc->conns[j] == nid)
					consumers++;
			}
		}
		/* The only exception is if real HP redirection is configured
		   and this is a duplication point.
		   XXX: Actually exception is not completely correct.
		   XXX: Duplication point check is not perfect. */
		if ((consumers == 2 && (w->bindas < 0 ||
		    as[w->bindas].hpredir < 0 || as[w->bindas].fakeredir ||
		    (w->bindseqmask & (1 << 15)) == 0)) ||
		    consumers > 2)
			return (found);

		/* Else use it's output mixer. */
		ctl = hdaa_audio_ctl_amp_get(devinfo, w->nid,
		    HDAA_CTL_OUT, -1, 1);
		if (ctl) {
			ctl->ossmask |= (1 << ossdev);
			found++;
			if (*minamp == *maxamp) {
				*minamp += MINQDB(ctl);
				*maxamp += MAXQDB(ctl);
			}
		}
	}

	/* We must not traverse pin */
	if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
	    depth > 0)
		return (found);

	cminamp = cmaxamp = 0;
	for (i = 0; i < w->nconns; i++) {
		if (w->connsenable[i] == 0)
			continue;
		if (index >= 0 && i != index)
			continue;
		tminamp = tmaxamp = 0;
		ctl = hdaa_audio_ctl_amp_get(devinfo, w->nid,
		    HDAA_CTL_IN, i, 1);
		if (ctl) {
			ctl->ossmask |= (1 << ossdev);
			found++;
			if (*minamp == *maxamp) {
				tminamp += MINQDB(ctl);
				tmaxamp += MAXQDB(ctl);
			}
		}
		found += hdaa_audio_ctl_dest_amp(devinfo, w->conns[i], -1, ossdev,
		    depth + 1, &tminamp, &tmaxamp);
		if (cminamp == 0 && cmaxamp == 0) {
			cminamp = tminamp;
			cmaxamp = tmaxamp;
		} else if (tminamp != tmaxamp) {
			cminamp = imax(cminamp, tminamp);
			cmaxamp = imin(cmaxamp, tmaxamp);
		}
	}
	if (*minamp == *maxamp && cminamp < cmaxamp) {
		*minamp += cminamp;
		*maxamp += cmaxamp;
	}
	return (found);
}