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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct TYPE_4__ {TYPE_1__ pin; } ;
struct hdaa_widget {scalar_t__ enable; scalar_t__ type; TYPE_2__ wclass; } ;
struct hdaa_devinfo {struct hdaa_audio_as* as; } ;
struct hdaa_audio_as {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int HDA_CONFIG_DEFAULTCONF_DEVICE (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdaa_chan_type(struct hdaa_devinfo *devinfo, int asid)
{
	struct hdaa_audio_as *as;
	struct hdaa_widget *w;
	int i, t = -1, t1;

	as = &devinfo->as[asid];
	for (i = 0; i < 16; i++) {
		w = hdaa_widget_get(devinfo, as->pins[i]);
		if (w == NULL || w->enable == 0 || w->type !=
		    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)
			continue;
		t1 = HDA_CONFIG_DEFAULTCONF_DEVICE(w->wclass.pin.config);
		if (t == -1)
			t = t1;
		else if (t != t1) {
			t = -2;
			break;
		}
	}
	return (t);
}