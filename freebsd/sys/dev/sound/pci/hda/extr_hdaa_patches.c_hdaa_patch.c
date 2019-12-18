#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int inamp_cap; } ;
struct TYPE_7__ {int config; } ;
struct TYPE_8__ {TYPE_2__ pin; } ;
struct hdaa_widget {TYPE_1__ param; int /*<<< orphan*/ * connsenable; int /*<<< orphan*/  enable; TYPE_3__ wclass; int /*<<< orphan*/  type; } ;
struct hdaa_devinfo {int startnode; int endnode; int /*<<< orphan*/  quirks; int /*<<< orphan*/  gpio; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  gpio; int /*<<< orphan*/  unset; int /*<<< orphan*/  set; int /*<<< orphan*/  subsystemid; int /*<<< orphan*/  id; int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int ASUS_A8X_SUBVENDOR ; 
 int /*<<< orphan*/  HDAA_QUIRK_EAPDINV ; 
#define  HDA_CODEC_AD1981HD 144 
#define  HDA_CODEC_AD1983 143 
#define  HDA_CODEC_AD1986A 142 
#define  HDA_CODEC_ALC269 141 
#define  HDA_CODEC_CX20582 140 
#define  HDA_CODEC_CX20583 139 
#define  HDA_CODEC_CX20584 138 
#define  HDA_CODEC_CX20585 137 
#define  HDA_CODEC_CX20590 136 
#define  HDA_CODEC_VT1708S_0 135 
#define  HDA_CODEC_VT1708S_1 134 
#define  HDA_CODEC_VT1708S_2 133 
#define  HDA_CODEC_VT1708S_3 132 
#define  HDA_CODEC_VT1708S_4 131 
#define  HDA_CODEC_VT1708S_5 130 
#define  HDA_CODEC_VT1708S_6 129 
#define  HDA_CODEC_VT1708S_7 128 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_NONE ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN ; 
 scalar_t__ HDA_DEV_MATCH (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_NUMSTEPS_SHIFT ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_OFFSET_SHIFT ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_STEPSIZE_SHIFT ; 
 int hda_get_subsystem_id (int /*<<< orphan*/ ) ; 
 int hdaa_card_id (struct hdaa_devinfo*) ; 
 int hdaa_codec_id (struct hdaa_devinfo*) ; 
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,int) ; 
 int /*<<< orphan*/  hdaa_widget_patch (struct hdaa_widget*) ; 
 TYPE_4__* hdac_quirks ; 
 int nitems (TYPE_4__*) ; 

void
hdaa_patch(struct hdaa_devinfo *devinfo)
{
	struct hdaa_widget *w;
	uint32_t id, subid, subsystemid;
	int i;

	id = hdaa_codec_id(devinfo);
	subid = hdaa_card_id(devinfo);
	subsystemid = hda_get_subsystem_id(devinfo->dev);

	/*
	 * Quirks
	 */
	for (i = 0; i < nitems(hdac_quirks); i++) {
		if (!(HDA_DEV_MATCH(hdac_quirks[i].model, subid) &&
		    HDA_DEV_MATCH(hdac_quirks[i].id, id) &&
		    HDA_DEV_MATCH(hdac_quirks[i].subsystemid, subsystemid)))
			continue;
		devinfo->quirks |= hdac_quirks[i].set;
		devinfo->quirks &= ~(hdac_quirks[i].unset);
		devinfo->gpio = hdac_quirks[i].gpio;
	}

	/* Apply per-widget patch. */
	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		w = hdaa_widget_get(devinfo, i);
		if (w == NULL)
			continue;
		hdaa_widget_patch(w);
	}

	switch (id) {
	case HDA_CODEC_AD1983:
		/*
		 * This CODEC has several possible usages, but none
		 * fit the parser best. Help parser to choose better.
		 */
		/* Disable direct unmixed playback to get pcm volume. */
		w = hdaa_widget_get(devinfo, 5);
		if (w != NULL)
			w->connsenable[0] = 0;
		w = hdaa_widget_get(devinfo, 6);
		if (w != NULL)
			w->connsenable[0] = 0;
		w = hdaa_widget_get(devinfo, 11);
		if (w != NULL)
			w->connsenable[0] = 0;
		/* Disable mic and line selectors. */
		w = hdaa_widget_get(devinfo, 12);
		if (w != NULL)
			w->connsenable[1] = 0;
		w = hdaa_widget_get(devinfo, 13);
		if (w != NULL)
			w->connsenable[1] = 0;
		/* Disable recording from mono playback mix. */
		w = hdaa_widget_get(devinfo, 20);
		if (w != NULL)
			w->connsenable[3] = 0;
		break;
	case HDA_CODEC_AD1986A:
		/*
		 * This CODEC has overcomplicated input mixing.
		 * Make some cleaning there.
		 */
		/* Disable input mono mixer. Not needed and not supported. */
		w = hdaa_widget_get(devinfo, 43);
		if (w != NULL)
			w->enable = 0;
		/* Disable any with any input mixing mesh. Use separately. */
		w = hdaa_widget_get(devinfo, 39);
		if (w != NULL)
			w->enable = 0;
		w = hdaa_widget_get(devinfo, 40);
		if (w != NULL)
			w->enable = 0;
		w = hdaa_widget_get(devinfo, 41);
		if (w != NULL)
			w->enable = 0;
		w = hdaa_widget_get(devinfo, 42);
		if (w != NULL)
			w->enable = 0;
		/* Disable duplicate mixer node connector. */
		w = hdaa_widget_get(devinfo, 15);
		if (w != NULL)
			w->connsenable[3] = 0;
		/* There is only one mic preamplifier, use it effectively. */
		w = hdaa_widget_get(devinfo, 31);
		if (w != NULL) {
			if ((w->wclass.pin.config &
			    HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) ==
			    HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN) {
				w = hdaa_widget_get(devinfo, 16);
				if (w != NULL)
				    w->connsenable[2] = 0;
			} else {
				w = hdaa_widget_get(devinfo, 15);
				if (w != NULL)
				    w->connsenable[0] = 0;
			}
		}
		w = hdaa_widget_get(devinfo, 32);
		if (w != NULL) {
			if ((w->wclass.pin.config &
			    HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) ==
			    HDA_CONFIG_DEFAULTCONF_DEVICE_MIC_IN) {
				w = hdaa_widget_get(devinfo, 16);
				if (w != NULL)
				    w->connsenable[0] = 0;
			} else {
				w = hdaa_widget_get(devinfo, 15);
				if (w != NULL)
				    w->connsenable[1] = 0;
			}
		}

		if (subid == ASUS_A8X_SUBVENDOR) {
			/*
			 * This is just plain ridiculous.. There
			 * are several A8 series that share the same
			 * pci id but works differently (EAPD).
			 */
			w = hdaa_widget_get(devinfo, 26);
			if (w != NULL && w->type ==
			    HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
			    (w->wclass.pin.config &
			    HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK) !=
			    HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_NONE)
				devinfo->quirks &=
				    ~HDAA_QUIRK_EAPDINV;
		}
		break;
	case HDA_CODEC_AD1981HD:
		/*
		 * This CODEC has very unusual design with several
		 * points inappropriate for the present parser.
		 */
		/* Disable recording from mono playback mix. */
		w = hdaa_widget_get(devinfo, 21);
		if (w != NULL)
			w->connsenable[3] = 0;
		/* Disable rear to front mic mixer, use separately. */
		w = hdaa_widget_get(devinfo, 31);
		if (w != NULL)
			w->enable = 0;
		/* Disable direct playback, use mixer. */
		w = hdaa_widget_get(devinfo, 5);
		if (w != NULL)
			w->connsenable[0] = 0;
		w = hdaa_widget_get(devinfo, 6);
		if (w != NULL)
			w->connsenable[0] = 0;
		w = hdaa_widget_get(devinfo, 9);
		if (w != NULL)
			w->connsenable[0] = 0;
		w = hdaa_widget_get(devinfo, 24);
		if (w != NULL)
			w->connsenable[0] = 0;
		break;
	case HDA_CODEC_ALC269:
		/*
		 * ASUS EeePC 1001px has strange variant of ALC269 CODEC,
		 * that mutes speaker if unused mixer at NID 15 is muted.
		 * Probably CODEC incorrectly reports internal connections.
		 * Hide that muter from the driver.  There are several CODECs
		 * sharing this ID and I have not enough information about
		 * them to implement more universal solution.
		 */
		if (subid == 0x84371043) {
			w = hdaa_widget_get(devinfo, 15);
			if (w != NULL)
				w->param.inamp_cap = 0;
		}
		break;
	case HDA_CODEC_CX20582:
	case HDA_CODEC_CX20583:
	case HDA_CODEC_CX20584:
	case HDA_CODEC_CX20585:
	case HDA_CODEC_CX20590:
		/*
		 * These codecs have extra connectivity on record side
		 * too reach for the present parser.
		 */
		w = hdaa_widget_get(devinfo, 20);
		if (w != NULL)
			w->connsenable[1] = 0;
		w = hdaa_widget_get(devinfo, 21);
		if (w != NULL)
			w->connsenable[1] = 0;
		w = hdaa_widget_get(devinfo, 22);
		if (w != NULL)
			w->connsenable[0] = 0;
		break;
	case HDA_CODEC_VT1708S_0:
	case HDA_CODEC_VT1708S_1:
	case HDA_CODEC_VT1708S_2:
	case HDA_CODEC_VT1708S_3:
	case HDA_CODEC_VT1708S_4:
	case HDA_CODEC_VT1708S_5:
	case HDA_CODEC_VT1708S_6:
	case HDA_CODEC_VT1708S_7:
		/*
		 * These codecs have hidden mic boost controls.
		 */
		w = hdaa_widget_get(devinfo, 26);
		if (w != NULL)
			w->param.inamp_cap =
			    (40 << HDA_PARAM_OUTPUT_AMP_CAP_STEPSIZE_SHIFT) |
			    (3 << HDA_PARAM_OUTPUT_AMP_CAP_NUMSTEPS_SHIFT) |
			    (0 << HDA_PARAM_OUTPUT_AMP_CAP_OFFSET_SHIFT);
		w = hdaa_widget_get(devinfo, 30);
		if (w != NULL)
			w->param.inamp_cap =
			    (40 << HDA_PARAM_OUTPUT_AMP_CAP_STEPSIZE_SHIFT) |
			    (3 << HDA_PARAM_OUTPUT_AMP_CAP_NUMSTEPS_SHIFT) |
			    (0 << HDA_PARAM_OUTPUT_AMP_CAP_OFFSET_SHIFT);
		break;
	}
}