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
struct hdaa_widget {scalar_t__ enable; int nid; char* name; scalar_t__ ossmask; scalar_t__ ossdev; int nconns; scalar_t__* connsenable; int bindas; int /*<<< orphan*/ * conns; } ;
struct hdaa_pcm_devinfo {int /*<<< orphan*/  dev; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int HDA_PARSE_MAXDEPTH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char*) ; 
 char* hdaa_audio_ctl_ossmixer_mask2allname (scalar_t__,char*,int) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
hdaa_dump_dst_nid(struct hdaa_pcm_devinfo *pdevinfo, nid_t nid, int depth)
{
	struct hdaa_devinfo *devinfo = pdevinfo->devinfo;
	struct hdaa_widget *w, *cw;
	char buf[64];
	int i;

	if (depth > HDA_PARSE_MAXDEPTH)
		return;

	w = hdaa_widget_get(devinfo, nid);
	if (w == NULL || w->enable == 0)
		return;

	if (depth == 0)
		device_printf(pdevinfo->dev, "%*s", 4, "");
	else
		device_printf(pdevinfo->dev, "%*s  + <- ", 4 + (depth - 1) * 7, "");
	printf("nid=%d [%s]", w->nid, w->name);

	if (depth > 0) {
		if (w->ossmask == 0) {
			printf("\n");
			return;
		}
		printf(" [src: %s]", 
		    hdaa_audio_ctl_ossmixer_mask2allname(
			w->ossmask, buf, sizeof(buf)));
		if (w->ossdev >= 0) {
			printf("\n");
			return;
		}
	}
	printf("\n");

	for (i = 0; i < w->nconns; i++) {
		if (w->connsenable[i] == 0)
			continue;
		cw = hdaa_widget_get(devinfo, w->conns[i]);
		if (cw == NULL || cw->enable == 0 || cw->bindas == -1)
			continue;
		hdaa_dump_dst_nid(pdevinfo, w->conns[i], depth + 1);
	}

}