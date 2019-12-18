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
typedef  int /*<<< orphan*/  uint32_t ;
struct hdaa_widget {scalar_t__ enable; size_t bindas; scalar_t__ type; int pflags; int nconns; int* conns; unsigned int ossdev; int /*<<< orphan*/  nid; int /*<<< orphan*/ * connsenable; } ;
struct hdaa_pcm_devinfo {int* left; int* maxamp; int* minamp; int* right; scalar_t__ index; size_t playas; size_t recas; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int startnode; int endnode; TYPE_1__* as; } ;
struct TYPE_2__ {scalar_t__ dir; } ;

/* Variables and functions */
 int HDAA_ADC_MONITOR ; 
 int /*<<< orphan*/  HDAA_AMP_MUTE_LEFT ; 
 int /*<<< orphan*/  HDAA_AMP_MUTE_RIGHT ; 
 scalar_t__ HDAA_CTL_IN ; 
 scalar_t__ HDAA_CTL_OUT ; 
 int HDAA_IMIX_AS_DST ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 unsigned int SOUND_MIXER_IGAIN ; 
 unsigned int SOUND_MIXER_IMIX ; 
 unsigned int SOUND_MIXER_RECLEV ; 
 unsigned int SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  hdaa_audio_ctl_dest_volume (struct hdaa_pcm_devinfo*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_audio_ctl_source_volume (struct hdaa_pcm_devinfo*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_audio_ctl_dev_volume(struct hdaa_pcm_devinfo *pdevinfo, unsigned dev)
{
	struct hdaa_devinfo *devinfo = pdevinfo->devinfo;
	struct hdaa_widget *w, *cw;
	uint32_t mute;
	int lvol, rvol;
	int i, j;

	mute = 0;
	if (pdevinfo->left[dev] == 0) {
		mute |= HDAA_AMP_MUTE_LEFT;
		lvol = -4000;
	} else
		lvol = ((pdevinfo->maxamp[dev] - pdevinfo->minamp[dev]) *
		    pdevinfo->left[dev] + 50) / 100 + pdevinfo->minamp[dev];
	if (pdevinfo->right[dev] == 0) {
		mute |= HDAA_AMP_MUTE_RIGHT;
		rvol = -4000;
	} else
		rvol = ((pdevinfo->maxamp[dev] - pdevinfo->minamp[dev]) *
		    pdevinfo->right[dev] + 50) / 100 + pdevinfo->minamp[dev];
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->bindas < 0) {
			if (pdevinfo->index != 0)
				continue;
		} else {
			if (w->bindas != pdevinfo->playas &&
			    w->bindas != pdevinfo->recas)
				continue;
		}
		if (dev == SOUND_MIXER_RECLEV &&
		    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT) {
			hdaa_audio_ctl_dest_volume(pdevinfo, dev,
			    w->nid, -1, mute, lvol, rvol, 0);
			continue;
		}
		if (dev == SOUND_MIXER_VOLUME &&
		    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
		    devinfo->as[w->bindas].dir == HDAA_CTL_OUT) {
			hdaa_audio_ctl_dest_volume(pdevinfo, dev,
			    w->nid, -1, mute, lvol, rvol, 0);
			continue;
		}
		if (dev == SOUND_MIXER_IGAIN &&
		    w->pflags & HDAA_ADC_MONITOR) {
			for (j = 0; j < w->nconns; j++) {
				if (!w->connsenable[j])
				    continue;
				cw = hdaa_widget_get(devinfo, w->conns[j]);
				if (cw == NULL || cw->enable == 0)
				    continue;
				if (cw->bindas == -1)
				    continue;
				if (cw->bindas >= 0 &&
				    devinfo->as[cw->bindas].dir != HDAA_CTL_IN)
					continue;
				hdaa_audio_ctl_dest_volume(pdevinfo, dev,
				    w->nid, j, mute, lvol, rvol, 0);
			}
			continue;
		}
		if (w->ossdev != dev)
			continue;
		hdaa_audio_ctl_source_volume(pdevinfo, dev,
		    w->nid, -1, mute, lvol, rvol, 0);
		if (dev == SOUND_MIXER_IMIX && (w->pflags & HDAA_IMIX_AS_DST))
			hdaa_audio_ctl_dest_volume(pdevinfo, dev,
			    w->nid, -1, mute, lvol, rvol, 0);
	}
}