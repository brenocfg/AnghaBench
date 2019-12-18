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

/* Variables and functions */
 int /*<<< orphan*/  MCFINTC_TIMER1 ; 
 int /*<<< orphan*/  MCFINTC_TIMER2 ; 
 int MCFSIM_ICR_AUTOVEC ; 
 int MCFSIM_ICR_LEVEL6 ; 
 int MCFSIM_ICR_LEVEL7 ; 
 int MCFSIM_ICR_PRI3 ; 
 int /*<<< orphan*/  MCFSIM_TIMER1ICR ; 
 int /*<<< orphan*/  MCFSIM_TIMER2ICR ; 
 int /*<<< orphan*/  MCF_IRQ_PROFILER ; 
 int /*<<< orphan*/  MCF_IRQ_TIMER ; 
 int /*<<< orphan*/  mcf_mapirq2imr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_timer_irq(void)
{
#ifdef MCFSIM_ICR_AUTOVEC
	/* Timer1 is always used as system timer */
	writeb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL6 | MCFSIM_ICR_PRI3,
		MCFSIM_TIMER1ICR);
	mcf_mapirq2imr(MCF_IRQ_TIMER, MCFINTC_TIMER1);

#ifdef CONFIG_HIGHPROFILE
	/* Timer2 is to be used as a high speed profile timer  */
	writeb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL7 | MCFSIM_ICR_PRI3,
		MCFSIM_TIMER2ICR);
	mcf_mapirq2imr(MCF_IRQ_PROFILER, MCFINTC_TIMER2);
#endif
#endif /* MCFSIM_ICR_AUTOVEC */
}