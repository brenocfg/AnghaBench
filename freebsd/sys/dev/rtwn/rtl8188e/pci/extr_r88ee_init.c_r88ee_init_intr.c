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
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r88ee_init_intr(struct rtwn_softc *sc)
{
	/* Disable interrupts. */
	rtwn_write_4(sc, R88E_HIMR, 0x00000000);
	rtwn_write_4(sc, R88E_HIMRE, 0x00000000);
}