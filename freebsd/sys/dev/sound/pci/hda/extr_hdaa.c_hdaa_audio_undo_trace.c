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
struct hdaa_widget {scalar_t__ enable; int bindas; int bindseqmask; int selconn; } ;
struct hdaa_devinfo {int startnode; int endnode; } ;

/* Variables and functions */
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 

__attribute__((used)) static void
hdaa_audio_undo_trace(struct hdaa_devinfo *devinfo, int as, int seq)
{
	struct hdaa_widget *w;
	int i;

	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->bindas == as) {
			if (seq >= 0) {
				w->bindseqmask &= ~(1 << seq);
				if (w->bindseqmask == 0) {
					w->bindas = -1;
					w->selconn = -1;
				}
			} else {
				w->bindas = -1;
				w->bindseqmask = 0;
				w->selconn = -1;
			}
		}
	}
}