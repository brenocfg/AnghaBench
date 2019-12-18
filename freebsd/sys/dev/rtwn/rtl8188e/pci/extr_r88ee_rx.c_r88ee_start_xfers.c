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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88E_HIMR ; 
 int /*<<< orphan*/  R88E_HIMRE ; 
 int /*<<< orphan*/  R88E_HISR ; 
 int /*<<< orphan*/  R88E_HISRE ; 
 int R88E_INT_ENABLE ; 
 int R88E_INT_ENABLE_EX ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r88ee_start_xfers(struct rtwn_softc *sc)
{
	/* Clear pending interrupts. */
	rtwn_write_4(sc, R88E_HISR, 0xffffffff);
	rtwn_write_4(sc, R88E_HISRE, 0xffffffff);

	/* Enable interrupts. */
	rtwn_write_4(sc, R88E_HIMR, R88E_INT_ENABLE);
	rtwn_write_4(sc, R88E_HIMRE, R88E_INT_ENABLE_EX);
}