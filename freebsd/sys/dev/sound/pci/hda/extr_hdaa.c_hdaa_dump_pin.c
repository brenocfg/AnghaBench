#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int cap; int config; int ctrl; } ;
struct TYPE_8__ {TYPE_3__ pin; } ;
struct TYPE_6__ {int /*<<< orphan*/  widget_cap; } ;
struct hdaa_widget {TYPE_4__ wclass; TYPE_2__ param; TYPE_1__* devinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_BALANCED_IO_PINS (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_DP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_EAPD_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HBR (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HDMI (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HEADPHONE_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_IMP_SENSE_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_INPUT_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_OUTPUT_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_PRESENCE_DETECT_CAP (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_TRIGGER_REQD (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_100 (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_50 (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_80 (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_GROUND (int) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_HIZ (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
hdaa_dump_pin(struct hdaa_widget *w)
{
	uint32_t pincap;

	pincap = w->wclass.pin.cap;

	device_printf(w->devinfo->dev, "        Pin cap: 0x%08x", pincap);
	if (HDA_PARAM_PIN_CAP_IMP_SENSE_CAP(pincap))
		printf(" ISC");
	if (HDA_PARAM_PIN_CAP_TRIGGER_REQD(pincap))
		printf(" TRQD");
	if (HDA_PARAM_PIN_CAP_PRESENCE_DETECT_CAP(pincap))
		printf(" PDC");
	if (HDA_PARAM_PIN_CAP_HEADPHONE_CAP(pincap))
		printf(" HP");
	if (HDA_PARAM_PIN_CAP_OUTPUT_CAP(pincap))
		printf(" OUT");
	if (HDA_PARAM_PIN_CAP_INPUT_CAP(pincap))
		printf(" IN");
	if (HDA_PARAM_PIN_CAP_BALANCED_IO_PINS(pincap))
		printf(" BAL");
	if (HDA_PARAM_PIN_CAP_HDMI(pincap))
		printf(" HDMI");
	if (HDA_PARAM_PIN_CAP_VREF_CTRL(pincap)) {
		printf(" VREF[");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_50(pincap))
			printf(" 50");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_80(pincap))
			printf(" 80");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_100(pincap))
			printf(" 100");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_GROUND(pincap))
			printf(" GROUND");
		if (HDA_PARAM_PIN_CAP_VREF_CTRL_HIZ(pincap))
			printf(" HIZ");
		printf(" ]");
	}
	if (HDA_PARAM_PIN_CAP_EAPD_CAP(pincap))
		printf(" EAPD");
	if (HDA_PARAM_PIN_CAP_DP(pincap))
		printf(" DP");
	if (HDA_PARAM_PIN_CAP_HBR(pincap))
		printf(" HBR");
	printf("\n");
	device_printf(w->devinfo->dev, "     Pin config: 0x%08x\n",
	    w->wclass.pin.config);
	device_printf(w->devinfo->dev, "    Pin control: 0x%08x", w->wclass.pin.ctrl);
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE)
		printf(" HP");
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE)
		printf(" IN");
	if (w->wclass.pin.ctrl & HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE)
		printf(" OUT");
	if (HDA_PARAM_AUDIO_WIDGET_CAP_DIGITAL(w->param.widget_cap)) {
		if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) == 0x03)
			printf(" HBR");
		else if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) != 0)
			printf(" EPTs");
	} else {
		if ((w->wclass.pin.ctrl &
		    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK) != 0)
			printf(" VREFs");
	}
	printf("\n");
}