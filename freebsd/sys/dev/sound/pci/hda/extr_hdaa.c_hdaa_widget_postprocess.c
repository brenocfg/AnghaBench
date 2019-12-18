#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t config; } ;
struct TYPE_6__ {TYPE_2__ pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  widget_cap; } ;
struct hdaa_widget {int type; int /*<<< orphan*/  name; TYPE_3__ wclass; TYPE_1__ param; } ;

/* Variables and functions */
 char** HDA_COLORS ; 
 size_t HDA_CONFIG_DEFAULTCONF_COLOR_MASK ; 
 size_t HDA_CONFIG_DEFAULTCONF_COLOR_SHIFT ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_SHIFT ; 
 size_t HDA_CONFIG_DEFAULTCONF_DEVICE_MASK ; 
 size_t HDA_CONFIG_DEFAULTCONF_DEVICE_SHIFT ; 
 char** HDA_CONNS ; 
 char** HDA_DEVS ; 
 int HDA_PARAM_AUDIO_WIDGET_CAP_TYPE (int /*<<< orphan*/ ) ; 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT 136 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER 135 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT 134 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_SELECTOR 133 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET 132 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX 131 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_POWER_WIDGET 130 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_VENDOR_WIDGET 129 
#define  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_VOLUME_WIDGET 128 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
hdaa_widget_postprocess(struct hdaa_widget *w)
{
	const char *typestr;

	w->type = HDA_PARAM_AUDIO_WIDGET_CAP_TYPE(w->param.widget_cap);
	switch (w->type) {
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT:
		typestr = "audio output";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT:
		typestr = "audio input";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER:
		typestr = "audio mixer";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_SELECTOR:
		typestr = "audio selector";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX:
		typestr = "pin";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_POWER_WIDGET:
		typestr = "power widget";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_VOLUME_WIDGET:
		typestr = "volume widget";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_BEEP_WIDGET:
		typestr = "beep widget";
		break;
	case HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_VENDOR_WIDGET:
		typestr = "vendor widget";
		break;
	default:
		typestr = "unknown type";
		break;
	}
	strlcpy(w->name, typestr, sizeof(w->name));

	if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX) {
		uint32_t config;
		const char *devstr;
		int conn, color;

		config = w->wclass.pin.config;
		devstr = HDA_DEVS[(config & HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) >>
		    HDA_CONFIG_DEFAULTCONF_DEVICE_SHIFT];
		conn = (config & HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK) >>
		    HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_SHIFT;
		color = (config & HDA_CONFIG_DEFAULTCONF_COLOR_MASK) >>
		    HDA_CONFIG_DEFAULTCONF_COLOR_SHIFT;
		strlcat(w->name, ": ", sizeof(w->name));
		strlcat(w->name, devstr, sizeof(w->name));
		strlcat(w->name, " (", sizeof(w->name));
		if (conn == 0 && color != 0 && color != 15) {
			strlcat(w->name, HDA_COLORS[color], sizeof(w->name));
			strlcat(w->name, " ", sizeof(w->name));
		}
		strlcat(w->name, HDA_CONNS[conn], sizeof(w->name));
		strlcat(w->name, ")", sizeof(w->name));
	}
}