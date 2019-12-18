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
struct ti_gpio_softc {int dummy; } ;
struct ti_gpio_irqsrc {int /*<<< orphan*/  tgi_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ti_gpio_intr_clr (struct ti_gpio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ti_gpio_isrc_mask(struct ti_gpio_softc *sc, struct ti_gpio_irqsrc *tgi)
{

	/* Writing a 0 has no effect. */
	ti_gpio_intr_clr(sc, tgi->tgi_mask);
}