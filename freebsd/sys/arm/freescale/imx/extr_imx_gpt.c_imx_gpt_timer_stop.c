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
struct imx_gpt_softc {int ir_reg; scalar_t__ sc_period; } ;
struct eventtimer {scalar_t__ et_priv; } ;

/* Variables and functions */
 int GPT_IR_OF2 ; 
 int GPT_IR_OF3 ; 
 int /*<<< orphan*/  IMX_GPT_IR ; 
 int /*<<< orphan*/  IMX_GPT_SR ; 
 int /*<<< orphan*/  WRITE4 (struct imx_gpt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
imx_gpt_timer_stop(struct eventtimer *et)
{
	struct imx_gpt_softc *sc;

	sc = (struct imx_gpt_softc *)et->et_priv;

	/* Disable interrupts and clear any pending status. */
	sc->ir_reg &= ~(GPT_IR_OF2 | GPT_IR_OF3);
	WRITE4(sc, IMX_GPT_IR, sc->ir_reg);
	WRITE4(sc, IMX_GPT_SR, GPT_IR_OF2 | GPT_IR_OF3);
	sc->sc_period = 0;

	return (0);
}