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
struct awg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_INT_EN ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
awg_disable_intr(struct awg_softc *sc)
{
	/* Disable interrupts */
	WR4(sc, EMAC_INT_EN, 0);
}