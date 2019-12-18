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
struct eventtimer {scalar_t__ et_priv; } ;
struct arm_tmr_softc {int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_tmr_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_tmr_stop(struct eventtimer *et)
{
	struct arm_tmr_softc *sc;

	sc = (struct arm_tmr_softc *)et->et_priv;
	arm_tmr_disable(sc->physical);

	return (0);
}