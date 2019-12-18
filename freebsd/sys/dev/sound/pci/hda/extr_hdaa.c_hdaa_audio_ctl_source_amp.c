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
struct hdaa_widget {scalar_t__ enable; int nconns; scalar_t__ type; scalar_t__ nid; scalar_t__ ossdev; int ossmask; scalar_t__* conns; scalar_t__* connsenable; } ;
struct hdaa_devinfo {int startnode; int endnode; } ;
struct hdaa_audio_ctl {int ossmask; } ;
typedef  scalar_t__ nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAA_CTL_IN ; 
 int /*<<< orphan*/  HDAA_CTL_OUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 int HDA_PARSE_MAXDEPTH ; 
 scalar_t__ MAXQDB (struct hdaa_audio_ctl*) ; 
 scalar_t__ MINQDB (struct hdaa_audio_ctl*) ; 
 struct hdaa_audio_ctl* hdaa_audio_ctl_amp_get (struct hdaa_devinfo*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 int imax (int,int) ; 
 int imin (int,int) ; 

__attribute__((used)) static int
hdaa_audio_ctl_source_amp(struct hdaa_devinfo *devinfo, nid_t nid, int index,
    int ossdev, int ctlable, int depth, int *minamp, int *maxamp)
{
	struct hdaa_widget *w, *wc;
	struct hdaa_audio_ctl *ctl;
	int i, j, conns = 0, tminamp, tmaxamp, cminamp, cmaxamp, found = 0;

	if (depth > HDA_PARSE_MAXDEPTH)
		return (found);

	w = hdaa_widget_get(devinfo, nid);
	if (w == NULL || w->enable == 0)
		return (found);

	/* Count number of active inputs. */
	if (depth > 0) {
		for (j = 0; j < w->nconns; j++) {
			if (!w->connsenable[j])
				continue;
			conns++;
		}
	}

	/* If this is not a first step - use input mixer.
	   Pins have common input ctl so care must be taken. */
	if (depth > 0 && ctlable && (conns == 1 ||
	    w->type != HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)) {
		ctl = hdaa_audio_ctl_amp_get(devinfo, w->nid, HDAA_CTL_IN,
		    index, 1);
		if (ctl) {
			ctl->ossmask |= (1 << ossdev);
			found++;
			if (*minamp == *maxamp) {
				*minamp += MINQDB(ctl);
				*maxamp += MAXQDB(ctl);
			}
		}
	}

	/* If widget has own ossdev - not traverse it.
	   It will be traversed on its own. */
	if (w->ossdev >= 0 && depth > 0)
		return (found);

	/* We must not traverse pin */
	if ((w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ||
	    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX) &&
	    depth > 0)
		return (found);

	/* record that this widget exports such signal, */
	w->ossmask |= (1 << ossdev);

	/*
	 * If signals mixed, we can't assign controls farther.
	 * Ignore this on depth zero. Caller must knows why.
	 */
	if (conns > 1 &&
	    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER)
		ctlable = 0;

	if (ctlable) {
		ctl = hdaa_audio_ctl_amp_get(devinfo, w->nid, HDAA_CTL_OUT, -1, 1);
		if (ctl) {
			ctl->ossmask |= (1 << ossdev);
			found++;
			if (*minamp == *maxamp) {
				*minamp += MINQDB(ctl);
				*maxamp += MAXQDB(ctl);
			}
		}
	}

	cminamp = cmaxamp = 0;
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		wc = hdaa_widget_get(devinfo, i);
		if (wc == NULL || wc->enable == 0)
			continue;
		for (j = 0; j < wc->nconns; j++) {
			if (wc->connsenable[j] && wc->conns[j] == nid) {
				tminamp = tmaxamp = 0;
				found += hdaa_audio_ctl_source_amp(devinfo,
				    wc->nid, j, ossdev, ctlable, depth + 1,
				    &tminamp, &tmaxamp);
				if (cminamp == 0 && cmaxamp == 0) {
					cminamp = tminamp;
					cmaxamp = tmaxamp;
				} else if (tminamp != tmaxamp) {
					cminamp = imax(cminamp, tminamp);
					cmaxamp = imin(cmaxamp, tmaxamp);
				}
			}
		}
	}
	if (*minamp == *maxamp && cminamp < cmaxamp) {
		*minamp += cminamp;
		*maxamp += cmaxamp;
	}
	return (found);
}