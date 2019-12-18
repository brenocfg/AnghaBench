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
struct hdaa_widget {scalar_t__ enable; scalar_t__ type; int unsol; int /*<<< orphan*/  nid; } ;
struct hdaa_devinfo {int startnode; int endnode; int /*<<< orphan*/  dev; int /*<<< orphan*/  poll_jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_UNSOL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HDA_CMD_SET_UNSOLICITED_RESPONSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_sense_deinit(struct hdaa_devinfo *devinfo)
{
	struct hdaa_widget *w;
	int i;

	callout_stop(&devinfo->poll_jack);
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0 || w->type !=
		    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)
			continue;
		if (w->unsol < 0)
			continue;
		hda_command(devinfo->dev,
		    HDA_CMD_SET_UNSOLICITED_RESPONSE(0, w->nid, 0));
		HDAC_UNSOL_FREE(
		    device_get_parent(devinfo->dev), devinfo->dev,
		    w->unsol);
		w->unsol = -1;
	}
}