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
typedef  int uint32_t ;
struct imx_gpt_softc {int sc_period; int ir_reg; } ;
struct eventtimer {scalar_t__ et_frequency; scalar_t__ et_priv; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int EINVAL ; 
 int GPT_IR_OF2 ; 
 int GPT_IR_OF3 ; 
 int /*<<< orphan*/  IMX_GPT_CNT ; 
 int /*<<< orphan*/  IMX_GPT_IR ; 
 int /*<<< orphan*/  IMX_GPT_OCR2 ; 
 int /*<<< orphan*/  IMX_GPT_OCR3 ; 
 int READ4 (struct imx_gpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct imx_gpt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

__attribute__((used)) static int
imx_gpt_timer_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct imx_gpt_softc *sc;
	uint32_t ticks;

	sc = (struct imx_gpt_softc *)et->et_priv;

	if (period != 0) {
		sc->sc_period = ((uint32_t)et->et_frequency * period) >> 32;
		/* Set expected value */
		WRITE4(sc, IMX_GPT_OCR2, READ4(sc, IMX_GPT_CNT) + sc->sc_period);
		/* Enable compare register 2 Interrupt */
		sc->ir_reg |= GPT_IR_OF2;
		WRITE4(sc, IMX_GPT_IR, sc->ir_reg);
		return (0);
	} else if (first != 0) {
		/* Enable compare register 3 interrupt if not already on. */
		if ((sc->ir_reg & GPT_IR_OF3) == 0) {
			sc->ir_reg |= GPT_IR_OF3;
			WRITE4(sc, IMX_GPT_IR, sc->ir_reg);
		}
		ticks = ((uint32_t)et->et_frequency * first) >> 32;
		/* Do not disturb, otherwise event will be lost */
		spinlock_enter();
		/* Set expected value */
		WRITE4(sc, IMX_GPT_OCR3, READ4(sc, IMX_GPT_CNT) + ticks);
		/* Now everybody can relax */
		spinlock_exit();
		return (0);
	}

	return (EINVAL);
}