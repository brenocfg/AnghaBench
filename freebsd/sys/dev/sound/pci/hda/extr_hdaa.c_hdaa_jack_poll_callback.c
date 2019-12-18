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
struct hdaa_widget {scalar_t__ enable; scalar_t__ type; } ;
struct hdaa_devinfo {scalar_t__ poll_ival; int ascnt; int /*<<< orphan*/  poll_jack; TYPE_1__* as; } ;
struct TYPE_2__ {scalar_t__ hpredir; int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,scalar_t__,void (*) (void*),struct hdaa_devinfo*) ; 
 int /*<<< orphan*/  hdaa_lock (struct hdaa_devinfo*) ; 
 int /*<<< orphan*/  hdaa_presence_handler (struct hdaa_widget*) ; 
 int /*<<< orphan*/  hdaa_unlock (struct hdaa_devinfo*) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdaa_jack_poll_callback(void *arg)
{
	struct hdaa_devinfo *devinfo = arg;
	struct hdaa_widget *w;
	int i;

	hdaa_lock(devinfo);
	if (devinfo->poll_ival == 0) {
		hdaa_unlock(devinfo);
		return;
	}
	for (i = 0; i < devinfo->ascnt; i++) {
		if (devinfo->as[i].hpredir < 0)
			continue;
		w = hdaa_widget_get(devinfo, devinfo->as[i].pins[15]);
		if (w == NULL || w->enable == 0 || w->type !=
		    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX)
			continue;
		hdaa_presence_handler(w);
	}
	callout_reset(&devinfo->poll_jack, devinfo->poll_ival,
	    hdaa_jack_poll_callback, devinfo);
	hdaa_unlock(devinfo);
}