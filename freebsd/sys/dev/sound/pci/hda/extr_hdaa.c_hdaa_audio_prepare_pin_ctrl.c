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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int ctrl; int config; int /*<<< orphan*/  cap; } ;
struct TYPE_4__ {TYPE_1__ pin; } ;
struct hdaa_widget {scalar_t__ type; scalar_t__ waspin; scalar_t__ enable; size_t bindas; TYPE_2__ wclass; } ;
struct hdaa_devinfo {int nodecnt; int quirks; scalar_t__ init_clear; struct hdaa_widget* widget; struct hdaa_audio_as* as; } ;
struct hdaa_audio_as {scalar_t__ enable; scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ HDAA_CTL_IN ; 
 int HDAA_QUIRK_IVREF100 ; 
 int HDAA_QUIRK_IVREF50 ; 
 int HDAA_QUIRK_IVREF80 ; 
 int HDAA_QUIRK_OVREF100 ; 
 int HDAA_QUIRK_OVREF50 ; 
 int HDAA_QUIRK_OVREF80 ; 
 int /*<<< orphan*/  HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_100 ; 
 int /*<<< orphan*/  HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_50 ; 
 int /*<<< orphan*/  HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_80 ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE (int /*<<< orphan*/ ) ; 
 int HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_HP_OUT ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_MASK ; 
 scalar_t__ HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX ; 
 scalar_t__ HDA_PARAM_PIN_CAP_HEADPHONE_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_INPUT_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_OUTPUT_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_100 (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_50 (int /*<<< orphan*/ ) ; 
 scalar_t__ HDA_PARAM_PIN_CAP_VREF_CTRL_80 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdaa_audio_prepare_pin_ctrl(struct hdaa_devinfo *devinfo)
{
	struct hdaa_audio_as *as = devinfo->as;
	struct hdaa_widget *w;
	uint32_t pincap;
	int i;

	for (i = 0; i < devinfo->nodecnt; i++) {
		w = &devinfo->widget[i];
		if (w == NULL)
			continue;
		if (w->type != HDA_PARAM_AUDIO_WIDGET_CAP_TYPE_PIN_COMPLEX &&
		    w->waspin == 0)
			continue;

		pincap = w->wclass.pin.cap;

		/* Disable everything. */
		if (devinfo->init_clear) {
			w->wclass.pin.ctrl &= ~(
		    	HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE |
		    	HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE |
		    	HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE |
		    	HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE_MASK);
		}

		if (w->enable == 0) {
			/* Pin is unused so left it disabled. */
			continue;
		} else if (w->waspin) {
			/* Enable input for beeper input. */
			w->wclass.pin.ctrl |=
			    HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE;
		} else if (w->bindas < 0 || as[w->bindas].enable == 0) {
			/* Pin is unused so left it disabled. */
			continue;
		} else if (as[w->bindas].dir == HDAA_CTL_IN) {
			/* Input pin, configure for input. */
			if (HDA_PARAM_PIN_CAP_INPUT_CAP(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_IN_ENABLE;

			if ((devinfo->quirks & HDAA_QUIRK_IVREF100) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_100(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_100);
			else if ((devinfo->quirks & HDAA_QUIRK_IVREF80) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_80(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_80);
			else if ((devinfo->quirks & HDAA_QUIRK_IVREF50) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_50(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_50);
		} else {
			/* Output pin, configure for output. */
			if (HDA_PARAM_PIN_CAP_OUTPUT_CAP(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_OUT_ENABLE;

			if (HDA_PARAM_PIN_CAP_HEADPHONE_CAP(pincap) &&
			    (w->wclass.pin.config &
			    HDA_CONFIG_DEFAULTCONF_DEVICE_MASK) ==
			    HDA_CONFIG_DEFAULTCONF_DEVICE_HP_OUT)
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_HPHN_ENABLE;

			if ((devinfo->quirks & HDAA_QUIRK_OVREF100) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_100(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_100);
			else if ((devinfo->quirks & HDAA_QUIRK_OVREF80) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_80(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_80);
			else if ((devinfo->quirks & HDAA_QUIRK_OVREF50) &&
			    HDA_PARAM_PIN_CAP_VREF_CTRL_50(pincap))
				w->wclass.pin.ctrl |=
				    HDA_CMD_SET_PIN_WIDGET_CTRL_VREF_ENABLE(
				    HDA_CMD_PIN_WIDGET_CTRL_VREF_ENABLE_50);
		}
	}
}