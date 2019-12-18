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
struct hdaa_widget {int dummy; } ;
struct hdaa_devinfo {int startnode; int endnode; } ;

/* Variables and functions */
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 int /*<<< orphan*/  hdaa_widget_postprocess (struct hdaa_widget*) ; 

__attribute__((used)) static void
hdaa_audio_postprocess(struct hdaa_devinfo *devinfo)
{
	struct hdaa_widget *w;
	int i;

	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL)
			continue;
		hdaa_widget_postprocess(w);
	}
}