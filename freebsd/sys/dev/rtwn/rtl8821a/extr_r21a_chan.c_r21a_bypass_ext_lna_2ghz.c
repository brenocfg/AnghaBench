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
 int /*<<< orphan*/  R12A_RFE_INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R12A_RFE_PINMUX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
r21a_bypass_ext_lna_2ghz(struct rtwn_softc *sc)
{
	rtwn_bb_setbits(sc, R12A_RFE_INV(0), 0x00100000, 0);
	rtwn_bb_setbits(sc, R12A_RFE_INV(0), 0x00400000, 0);
	rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0), 0, 0x07);
	rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0), 0, 0x0700);
}