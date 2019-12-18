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
struct rt_softc {int intr_disable_mask; int intr_enable_mask; int /*<<< orphan*/  fe_int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rt_intr_enable(struct rt_softc *sc, uint32_t intr_mask)
{
	uint32_t tmp;

	sc->intr_disable_mask &= ~intr_mask;
	tmp = sc->intr_enable_mask & ~sc->intr_disable_mask;
	RT_WRITE(sc, sc->fe_int_enable, tmp);
}