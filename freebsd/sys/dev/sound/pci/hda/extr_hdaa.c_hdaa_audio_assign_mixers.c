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
struct hdaa_widget {scalar_t__ enable; scalar_t__ type; size_t bindas; scalar_t__ ossdev; int pflags; int nconns; int* conns; int /*<<< orphan*/  nid; int /*<<< orphan*/ * connsenable; } ;
struct hdaa_devinfo {int startnode; int endnode; struct hdaa_audio_as* as; } ;
struct hdaa_audio_as {scalar_t__ dir; } ;

/* Variables and functions */
 int HDAA_ADC_MONITOR ; 
 scalar_t__ HDAA_CTL_IN ; 
 scalar_t__ HDAA_CTL_OUT ; 
 int HDAA_IMIX_AS_DST ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 scalar_t__ SOUND_MIXER_IGAIN ; 
 scalar_t__ SOUND_MIXER_IMIX ; 
 scalar_t__ SOUND_MIXER_RECLEV ; 
 scalar_t__ SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  hdaa_adjust_amp (struct hdaa_widget*,scalar_t__,int,int,int) ; 
 int hdaa_audio_ctl_dest_amp (struct hdaa_devinfo*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int*,int*) ; 
 int hdaa_audio_ctl_source_amp (struct hdaa_devinfo*,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ,int*,int*) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_audio_assign_mixers(struct hdaa_devinfo *devinfo)
{
	struct hdaa_audio_as *as = devinfo->as;
	struct hdaa_widget *w, *cw;
	int i, j, minamp, maxamp, found;

	/* Assign mixers to the tree. */
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		minamp = maxamp = 0;
		if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT ||
		    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET ||
		    (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
		    as[w->bindas].dir == HDAA_CTL_IN)) {
			if (w->ossdev < 0)
				continue;
			found = hdaa_audio_ctl_source_amp(devinfo, w->nid, -1,
			    w->ossdev, 1, 0, &minamp, &maxamp);
			hdaa_adjust_amp(w, w->ossdev, found, minamp, maxamp);
		} else if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT) {
			found = hdaa_audio_ctl_dest_amp(devinfo, w->nid, -1,
			    SOUND_MIXER_RECLEV, 0, &minamp, &maxamp);
			hdaa_adjust_amp(w, SOUND_MIXER_RECLEV, found, minamp, maxamp);
		} else if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
		    as[w->bindas].dir == HDAA_CTL_OUT) {
			found = hdaa_audio_ctl_dest_amp(devinfo, w->nid, -1,
			    SOUND_MIXER_VOLUME, 0, &minamp, &maxamp);
			hdaa_adjust_amp(w, SOUND_MIXER_VOLUME, found, minamp, maxamp);
		}
		if (w->ossdev == SOUND_MIXER_IMIX) {
			minamp = maxamp = 0;
			found = hdaa_audio_ctl_source_amp(devinfo, w->nid, -1,
			    w->ossdev, 1, 0, &minamp, &maxamp);
			if (minamp == maxamp) {
				/* If we are unable to control input monitor
				   as source - try to control it as destination. */
				found += hdaa_audio_ctl_dest_amp(devinfo, w->nid, -1,
				    w->ossdev, 0, &minamp, &maxamp);
				w->pflags |= HDAA_IMIX_AS_DST;
			}
			hdaa_adjust_amp(w, w->ossdev, found, minamp, maxamp);
		}
		if (w->pflags & HDAA_ADC_MONITOR) {
			for (j = 0; j < w->nconns; j++) {
				if (!w->connsenable[j])
				    continue;
				cw = hdaa_widget_get(devinfo, w->conns[j]);
				if (cw == NULL || cw->enable == 0)
				    continue;
				if (cw->bindas == -1)
				    continue;
				if (cw->bindas >= 0 &&
				    as[cw->bindas].dir != HDAA_CTL_IN)
					continue;
				minamp = maxamp = 0;
				found = hdaa_audio_ctl_dest_amp(devinfo,
				    w->nid, j, SOUND_MIXER_IGAIN, 0,
				    &minamp, &maxamp);
				hdaa_adjust_amp(w, SOUND_MIXER_IGAIN,
				    found, minamp, maxamp);
			}
		}
	}
}