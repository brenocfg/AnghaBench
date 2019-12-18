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
struct TYPE_2__ {int /*<<< orphan*/  widget_cap; } ;
struct hdaa_widget {TYPE_1__ param; } ;
struct hdaa_devinfo {int /*<<< orphan*/  dev; } ;
struct hdaa_chan {int flags; scalar_t__ dir; int* io; int /*<<< orphan*/  sid; struct hdaa_devinfo* devinfo; } ;

/* Variables and functions */
 int HDAA_CHN_RUNNING ; 
 int /*<<< orphan*/  HDAC_STREAM_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDAC_STREAM_STOP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_SET_CONV_STREAM_CHAN (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_SET_DIGITAL_CONV_FMT1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_channel_stop(struct hdaa_chan *ch)
{
	struct hdaa_devinfo *devinfo = ch->devinfo;
	struct hdaa_widget *w;
	int i;

	if ((ch->flags & HDAA_CHN_RUNNING) == 0)
		return;
	ch->flags &= ~HDAA_CHN_RUNNING;
	HDAC_STREAM_STOP(device_get_parent(devinfo->dev), devinfo->dev,
	    ch->dir == PCMDIR_PLAY ? 1 : 0, ch->sid);
	for (i = 0; ch->io[i] != -1; i++) {
		w = hdaa_widget_get(ch->devinfo, ch->io[i]);
		if (w == NULL)
			continue;
		if (HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL(w->param.widget_cap)) {
			hda_command(devinfo->dev,
			    HDA_CMD_SET_DIGITAL_CONV_FMT1(0, ch->io[i], 0));
		}
		hda_command(devinfo->dev,
		    HDA_CMD_SET_CONV_STREAM_CHAN(0, ch->io[i],
		    0));
	}
	HDAC_STREAM_FREE(device_get_parent(devinfo->dev), devinfo->dev,
	    ch->dir == PCMDIR_PLAY ? 1 : 0, ch->sid);
}