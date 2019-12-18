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
struct hdaa_widget {scalar_t__ enable; scalar_t__ type; size_t bindas; } ;
struct hdaa_pcm_devinfo {size_t recas; int /*<<< orphan*/  dev; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int startnode; int endnode; TYPE_2__* chans; TYPE_1__* as; } ;
typedef  int nid_t ;
struct TYPE_4__ {int* io; int /*<<< orphan*/  supp_pcm_size_rate; int /*<<< orphan*/  supp_stream_formats; } ;
struct TYPE_3__ {int* chans; int num_chans; } ;

/* Variables and functions */
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdaa_dump_audio_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_dump_dst_nid (struct hdaa_pcm_devinfo*,int,int /*<<< orphan*/ ) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
hdaa_dump_adc(struct hdaa_pcm_devinfo *pdevinfo)
{
	struct hdaa_devinfo *devinfo = pdevinfo->devinfo;
	struct hdaa_widget *w;
	nid_t *nids;
	int chid, i;

	if (pdevinfo->recas < 0)
		return;

	device_printf(pdevinfo->dev, "Record:\n");

	chid = devinfo->as[pdevinfo->recas].chans[0];
	hdaa_dump_audio_formats(pdevinfo->dev,
	    devinfo->chans[chid].supp_stream_formats,
	    devinfo->chans[chid].supp_pcm_size_rate);
	for (i = 0; i < devinfo->as[pdevinfo->recas].num_chans; i++) {
		chid = devinfo->as[pdevinfo->recas].chans[i];
		device_printf(pdevinfo->dev, "            ADC:");
		for (nids = devinfo->chans[chid].io; *nids != -1; nids++)
			printf(" %d", *nids);
		printf("\n");
	}

	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL || w->enable == 0)
			continue;
		if (w->type != HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT)
			continue;
		if (w->bindas != pdevinfo->recas)
			continue;
		device_printf(pdevinfo->dev, "\n");
		hdaa_dump_dst_nid(pdevinfo, i, 0);
	}
	device_printf(pdevinfo->dev, "\n");
}