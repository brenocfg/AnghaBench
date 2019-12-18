#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct imx_gpt_softc {scalar_t__ sc_period; TYPE_1__ et; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int GPT_IR_OF2 ; 
 int GPT_IR_OF3 ; 
 int /*<<< orphan*/  IMX_GPT_CNT ; 
 int /*<<< orphan*/  IMX_GPT_OCR2 ; 
 int /*<<< orphan*/  IMX_GPT_SR ; 
 int READ4 (struct imx_gpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct imx_gpt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_gpt_intr(void *arg)
{
	struct imx_gpt_softc *sc;
	uint32_t status;

	sc = (struct imx_gpt_softc *)arg;

	status = READ4(sc, IMX_GPT_SR);

	/*
	* Clear interrupt status before invoking event callbacks.  The callback
	* often sets up a new one-shot timer event and if the interval is short
	* enough it can fire before we get out of this function.  If we cleared
	* at the bottom we'd miss the interrupt and hang until the clock wraps.
	*/
	WRITE4(sc, IMX_GPT_SR, status);

	/* Handle one-shot timer events. */
	if (status & GPT_IR_OF3) {
		if (sc->et.et_active) {
			sc->et.et_event_cb(&sc->et, sc->et.et_arg);
		}
	}

	/* Handle periodic timer events. */
	if (status & GPT_IR_OF2) {
		if (sc->et.et_active)
			sc->et.et_event_cb(&sc->et, sc->et.et_arg);
		if (sc->sc_period != 0)
			WRITE4(sc, IMX_GPT_OCR2, READ4(sc, IMX_GPT_CNT) +
			    sc->sc_period);
	}

	return (FILTER_HANDLED);
}