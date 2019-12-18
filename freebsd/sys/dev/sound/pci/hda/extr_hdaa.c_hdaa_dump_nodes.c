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
struct TYPE_6__ {int widget_cap; scalar_t__ outamp_cap; scalar_t__ inamp_cap; int /*<<< orphan*/  eapdbtl; int /*<<< orphan*/  supp_pcm_size_rate; int /*<<< orphan*/  supp_stream_formats; } ;
struct TYPE_4__ {int /*<<< orphan*/  stripecap; } ;
struct TYPE_5__ {TYPE_1__ conv; } ;
struct hdaa_widget {scalar_t__ enable; char* name; int bindas; scalar_t__ ossmask; size_t ossdev; scalar_t__ type; int nconns; int* conns; scalar_t__* connsenable; int selconn; TYPE_3__ param; scalar_t__ waspin; int /*<<< orphan*/  bindseqmask; TYPE_2__ wclass; int /*<<< orphan*/  nid; } ;
struct hdaa_devinfo {scalar_t__ inamp_cap; scalar_t__ outamp_cap; int startnode; int endnode; int /*<<< orphan*/  dev; int /*<<< orphan*/  supp_pcm_size_rate; int /*<<< orphan*/  supp_stream_formats; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_INVALID ; 
 int HDA_PARAM_AUDIO_WIDGET_CAP_CC (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_IN_AMP (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_LR_SWAP (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_OUT_AMP (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_POWER_CTRL (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_PROC_WIDGET (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_STRIPE (int) ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_UNSOL_CAP (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_audio_ctl_ossmixer_mask2allname (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  hdaa_dump_amp (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  hdaa_dump_audio_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_dump_pin (struct hdaa_widget*) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 char** ossnames ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
hdaa_dump_nodes(struct hdaa_devinfo *devinfo)
{
	struct hdaa_widget *w, *cw;
	char buf[64];
	int i, j;

	device_printf(devinfo->dev, "\n");
	device_printf(devinfo->dev, "Default parameters:\n");
	hdaa_dump_audio_formats(devinfo->dev,
	    devinfo->supp_stream_formats,
	    devinfo->supp_pcm_size_rate);
	hdaa_dump_amp(devinfo->dev, devinfo->inamp_cap, " Input");
	hdaa_dump_amp(devinfo->dev, devinfo->outamp_cap, "Output");
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL) {
			device_printf(devinfo->dev, "Ghost widget nid=%d\n", i);
			continue;
		}
		device_printf(devinfo->dev, "\n");
		device_printf(devinfo->dev, "            nid: %d%s\n", w->nid,
		    (w->enable == 0) ? " [DISABLED]" : "");
		device_printf(devinfo->dev, "           Name: %s\n", w->name);
		device_printf(devinfo->dev, "     Widget cap: 0x%08x",
		    w->param.widget_cap);
		if (w->param.widget_cap & 0x0ee1) {
			if (HDA_PARAM_AUDIO_WIDGET_CAP_LR_SWAP(w->param.widget_cap))
			    printf(" LRSWAP");
			if (HDA_PARAM_AUDIO_WIDGET_CAP_POWER_CTRL(w->param.widget_cap))
			    printf(" PWR");
			if (HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL(w->param.widget_cap))
			    printf(" DIGITAL");
			if (HDA_PARAM_AUDIO_WIDGET_CAP_UNSOL_CAP(w->param.widget_cap))
			    printf(" UNSOL");
			if (HDA_PARAM_AUDIO_WIDGET_CAP_PROC_WIDGET(w->param.widget_cap))
			    printf(" PROC");
			if (HDA_PARAM_AUDIO_WIDGET_CAP_STRIPE(w->param.widget_cap))
			    printf(" STRIPE(x%d)",
				1 << (fls(w->wclass.conv.stripecap) - 1));
			j = HDA_PARAM_AUDIO_WIDGET_CAP_CC(w->param.widget_cap);
			if (j == 1)
			    printf(" STEREO");
			else if (j > 1)
			    printf(" %dCH", j + 1);
		}
		printf("\n");
		if (w->bindas != -1) {
			device_printf(devinfo->dev, "    Association: %d (0x%04x)\n",
			    w->bindas, w->bindseqmask);
		}
		if (w->ossmask != 0 || w->ossdev >= 0) {
			device_printf(devinfo->dev, "            OSS: %s",
			    hdaa_audio_ctl_ossmixer_mask2allname(w->ossmask, buf, sizeof(buf)));
			if (w->ossdev >= 0)
			    printf(" (%s)", ossnames[w->ossdev]);
			printf("\n");
		}
		if (w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_OUTPUT ||
		    w->type == HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_INPUT) {
			hdaa_dump_audio_formats(devinfo->dev,
			    w->param.supp_stream_formats,
			    w->param.supp_pcm_size_rate);
		} else if (w->type ==
		    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX || w->waspin)
			hdaa_dump_pin(w);
		if (w->param.eapdbtl != HDA_INVALID)
			device_printf(devinfo->dev, "           EAPD: 0x%08x\n",
			    w->param.eapdbtl);
		if (HDA_PARAM_AUDIO_WIDGET_CAP_OUT_AMP(w->param.widget_cap) &&
		    w->param.outamp_cap != 0)
			hdaa_dump_amp(devinfo->dev, w->param.outamp_cap, "Output");
		if (HDA_PARAM_AUDIO_WIDGET_CAP_IN_AMP(w->param.widget_cap) &&
		    w->param.inamp_cap != 0)
			hdaa_dump_amp(devinfo->dev, w->param.inamp_cap, " Input");
		if (w->nconns > 0)
			device_printf(devinfo->dev, "    Connections: %d\n", w->nconns);
		for (j = 0; j < w->nconns; j++) {
			cw = hdaa_widget_get(devinfo, w->conns[j]);
			device_printf(devinfo->dev, "          + %s<- nid=%d [%s]",
			    (w->connsenable[j] == 0)?"[DISABLED] ":"",
			    w->conns[j], (cw == NULL) ? "GHOST!" : cw->name);
			if (cw == NULL)
				printf(" [UNKNOWN]");
			else if (cw->enable == 0)
				printf(" [DISABLED]");
			if (w->nconns > 1 && w->selconn == j && w->type !=
			    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_AUDIO_MIXER)
				printf(" (selected)");
			printf("\n");
		}
	}

}