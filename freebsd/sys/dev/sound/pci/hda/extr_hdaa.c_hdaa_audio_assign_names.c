#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int config; } ;
struct TYPE_4__ {TYPE_1__ pin; } ;
struct hdaa_widget {scalar_t__ enable; int bindas; int type; int ossdev; TYPE_2__ wclass; } ;
struct hdaa_devinfo {int startnode; int endnode; struct hdaa_audio_as* as; } ;
struct hdaa_audio_as {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ HDAA_CTL_OUT ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_JACK ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK ; 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_AUX 156 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_CD 155 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_DIGITAL_OTHER_IN 154 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_DIGITAL_OTHER_OUT 153 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_HP_OUT 152 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_LINE_IN 151 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_LINE_OUT 150 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_MASK ; 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN 149 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_SPDIF_IN 148 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_SPDIF_OUT 147 
#define  HDA_CONFIG_DEFAULTCONF_DEVICE_SPEAKER 146 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT 145 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET 144 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX 143 
#define  SOUND_MIXER_CD 142 
#define  SOUND_MIXER_DIGITAL1 141 
#define  SOUND_MIXER_DIGITAL2 140 
#define  SOUND_MIXER_DIGITAL3 139 
#define  SOUND_MIXER_LINE 138 
#define  SOUND_MIXER_LINE1 137 
#define  SOUND_MIXER_LINE2 136 
#define  SOUND_MIXER_LINE3 135 
#define  SOUND_MIXER_MIC 134 
#define  SOUND_MIXER_MONITOR 133 
 int SOUND_MIXER_PCM ; 
#define  SOUND_MIXER_PHONEIN 132 
#define  SOUND_MIXER_PHONEOUT 131 
#define  SOUND_MIXER_RADIO 130 
#define  SOUND_MIXER_SPEAKER 129 
#define  SOUND_MIXER_VIDEO 128 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_audio_assign_names(struct hdaa_devinfo *devinfo)
{
	struct hdaa_audio_as *as = devinfo->as;
	struct hdaa_widget *w;
	int i, j;
	int type = -1, use, used = 0;
	static const int types[7][13] = {
	    { SOUND_MIXER_LINE, SOUND_MIXER_LINE1, SOUND_MIXER_LINE2, 
	      SOUND_MIXER_LINE3, -1 },	/* line */
	    { SOUND_MIXER_MONITOR, SOUND_MIXER_MIC, -1 }, /* int mic */
	    { SOUND_MIXER_MIC, SOUND_MIXER_MONITOR, -1 }, /* ext mic */
	    { SOUND_MIXER_CD, -1 },	/* cd */
	    { SOUND_MIXER_SPEAKER, -1 },	/* speaker */
	    { SOUND_MIXER_DIGITAL1, SOUND_MIXER_DIGITAL2, SOUND_MIXER_DIGITAL3,
	      -1 },	/* digital */
	    { SOUND_MIXER_LINE, SOUND_MIXER_LINE1, SOUND_MIXER_LINE2,
	      SOUND_MIXER_LINE3, SOUND_MIXER_PHONEIN, SOUND_MIXER_PHONEOUT,
	      SOUND_MIXER_VIDEO, SOUND_MIXER_RADIO, SOUND_MIXER_DIGITAL1,
	      SOUND_MIXER_DIGITAL2, SOUND_MIXER_DIGITAL3, SOUND_MIXER_MONITOR,
	      -1 }	/* others */
	};

	/* Surely known names */
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->bindas == -1)
			continue;
		use = -1;
		switch (w->type) {
		case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX:
			if (as[w->bindas].dir == HDAA_CTL_OUT)
				break;
			type = -1;
			switch (w->wclass.pin.config & HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) {
			case HDA_CONFIG_DEFAULTCONF_DEVICE_LINE_IN:
				type = 0;
				break;
			case HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN:
				if ((w->wclass.pin.config & HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK)
				    == HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_JACK)
					break;
				type = 1;
				break;
			case HDA_CONFIG_DEFAULTCONF_DEVICE_CD:
				type = 3;
				break;
			case HDA_CONFIG_DEFAULTCONF_DEVICE_SPEAKER:
				type = 4;
				break;
			case HDA_CONFIG_DEFAULTCONF_DEVICE_SPDIF_IN:
			case HDA_CONFIG_DEFAULTCONF_DEVICE_DIGITAL_OTHER_IN:
				type = 5;
				break;
			}
			if (type == -1)
				break;
			j = 0;
			while (types[type][j] >= 0 &&
			    (used & (1 << types[type][j])) != 0) {
				j++;
			}
			if (types[type][j] >= 0)
				use = types[type][j];
			break;
		case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT:
			use = SOUND_MIXER_PCM;
			break;
		case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET:
			use = SOUND_MIXER_SPEAKER;
			break;
		default:
			break;
		}
		if (use >= 0) {
			w->ossdev = use;
			used |= (1 << use);
		}
	}
	/* Semi-known names */
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->ossdev >= 0)
			continue;
		if (w->bindas == -1)
			continue;
		if (w->type != HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)
			continue;
		if (as[w->bindas].dir == HDAA_CTL_OUT)
			continue;
		type = -1;
		switch (w->wclass.pin.config & HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) {
		case HDA_CONFIG_DEFAULTCONF_DEVICE_LINE_OUT:
		case HDA_CONFIG_DEFAULTCONF_DEVICE_SPEAKER:
		case HDA_CONFIG_DEFAULTCONF_DEVICE_HP_OUT:
		case HDA_CONFIG_DEFAULTCONF_DEVICE_AUX:
			type = 0;
			break;
		case HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN:
			type = 2;
			break;
		case HDA_CONFIG_DEFAULTCONF_DEVICE_SPDIF_OUT:
		case HDA_CONFIG_DEFAULTCONF_DEVICE_DIGITAL_OTHER_OUT:
			type = 5;
			break;
		}
		if (type == -1)
			break;
		j = 0;
		while (types[type][j] >= 0 &&
		    (used & (1 << types[type][j])) != 0) {
			j++;
		}
		if (types[type][j] >= 0) {
			w->ossdev = types[type][j];
			used |= (1 << types[type][j]);
		}
	}
	/* Others */
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->ossdev >= 0)
			continue;
		if (w->bindas == -1)
			continue;
		if (w->type != HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)
			continue;
		if (as[w->bindas].dir == HDAA_CTL_OUT)
			continue;
		j = 0;
		while (types[6][j] >= 0 &&
		    (used & (1 << types[6][j])) != 0) {
			j++;
		}
		if (types[6][j] >= 0) {
			w->ossdev = types[6][j];
			used |= (1 << types[6][j]);
		}
	}
}