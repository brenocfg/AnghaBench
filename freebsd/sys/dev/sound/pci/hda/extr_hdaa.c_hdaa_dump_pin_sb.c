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
typedef  int /*<<< orphan*/  uint32_t ;
struct sbuf {int dummy; } ;
struct TYPE_5__ {int ctrl; int /*<<< orphan*/  config; int /*<<< orphan*/  cap; } ;
struct TYPE_6__ {TYPE_2__ pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  widget_cap; } ;
struct hdaa_widget {TYPE_3__ wclass; TYPE_1__ param; } ;

/* Variables and functions */
 int HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK ; 
 int /*<<< orphan*/ * HDA_COLORS ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_ASSOCIATION (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_COLOR (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_CONNECTIVITY (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_DEVICE (int /*<<< orphan*/ ) ; 
 size_t HDA_CONFIG_DEFAULTCONF_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_MISC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CONFIG_DEFAULTCONF_SEQUENCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HDA_CONNECTORS ; 
 int /*<<< orphan*/ * HDA_CONNS ; 
 int /*<<< orphan*/ * HDA_DEVS ; 
 int /*<<< orphan*/ * HDA_LOCS ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_BALANCED_IO_PINS (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_DP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_EAPD_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HBR (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HDMI (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HEADPHONE_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_IMP_SENSE_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_INPUT_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_OUTPUT_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_PRESENCE_DETECT_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_TRIGGER_REQD (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_100 (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_50 (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_80 (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_GROUND (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_HIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
hdaa_dump_pin_sb(struct sbuf *sb, struct hdaa_widget *w)
{
	uint32_t pincap, conf;

	pincap = w->wclass.pin.cap;

	sbuf_printf(sb, "        Pin cap: 0x%08x", pincap);
	if (HDA_PARAM_PIN_CAP_IMP_SENSE_CAP(pincap))
		sbuf_printf(sb, " ISC");
	if (HDA_PARAM_PIN_CAP_TRIGGER_REQD(pincap))
		sbuf_printf(sb, " TRQD");
	if (HDA_PARAM_PIN_CAP_PRESENCE_DETECT_CAP(pincap))
		sbuf_printf(sb, " PDC");
	if (HDA_PARAM_PIN_CAP_HEADPHONE_CAP(pincap))
		sbuf_printf(sb, " HP");
	if (HDA_PARAM_PIN_CAP_OUTPUT_CAP(pincap))
		sbuf_printf(sb, " OUT");
	if (HDA_PARAM_PIN_CAP_INPUT_CAP(pincap))
		sbuf_printf(sb, " IN");
	if (HDA_PARAM_PIN_CAP_BALANCED_IO_PINS(pincap))
		sbuf_printf(sb, " BAL");
	if (HDA_PARAM_PIN_CAP_HDMI(pincap))
		sbuf_printf(sb, " HDMI");
	if (HDA_PARAM_PIN_CAP_VREF_CTRL(pincap)) {
		sbuf_printf(sb, " VREF[");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_50(pincap))
			sbuf_printf(sb, " 50");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_80(pincap))
			sbuf_printf(sb, " 80");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_100(pincap))
			sbuf_printf(sb, " 100");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_GROUND(pincap))
			sbuf_printf(sb, " GROUND");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_HIZ(pincap))
			sbuf_printf(sb, " HIZ");
		sbuf_printf(sb, " ]");
	}
	if (HDA_PARAM_PIN_CAP_EAPD_CAP(pincap))
		sbuf_printf(sb, " EAPD");
	if (HDA_PARAM_PIN_CAP_DP(pincap))
		sbuf_printf(sb, " DP");
	if (HDA_PARAM_PIN_CAP_HBR(pincap))
		sbuf_printf(sb, " HBR");
	sbuf_printf(sb, "\n");
	conf = w->wclass.pin.config;
	sbuf_printf(sb, "     Pin config: 0x%08x", conf);
	sbuf_printf(sb, " as=%d seq=%d "
	    "device=%s conn=%s ctype=%s loc=%s color=%s misc=%d\n",
	    HDA_CONFIG_DEFAULTCONF_ASSOCIATION(conf),
	    HDA_CONFIG_DEFAULTCONF_SEQUENCE(conf),
	    HDA_DEVS[HDA_CONFIG_DEFAULTCONF_DEVICE(conf)],
	    HDA_CONNS[HDA_CONFIG_DEFAULTCONF_CONNECTIVITY(conf)],
	    HDA_CONNECTORS[HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE(conf)],
	    HDA_LOCS[HDA_CONFIG_DEFAULTCONF_LOCATION(conf)],
	    HDA_COLORS[HDA_CONFIG_DEFAULTCONF_COLOR(conf)],
	    HDA_CONFIG_DEFAULTCONF_MISC(conf));
	sbuf_printf(sb, "    Pin control: 0x%08x", w->wclass.pin.ctrl);
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE)
		sbuf_printf(sb, " HP");
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE)
		sbuf_printf(sb, " IN");
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE)
		sbuf_printf(sb, " OUT");
	if (HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL(w->param.widget_cap)) {
		if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) == 0x03)
			sbuf_printf(sb, " HBR");
		else if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) != 0)
			sbuf_printf(sb, " EPTs");
	} else {
		if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) != 0)
			sbuf_printf(sb, " VREFs");
	}
	sbuf_printf(sb, "\n");
}