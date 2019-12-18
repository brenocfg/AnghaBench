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
 int /*<<< orphan*/  R92C_OFDM0_AGCCORE1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r88e_crystalcap_write (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r92c_init_bb_common (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_bb_write (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 

void
r88e_init_bb_common(struct rtwn_softc *sc)
{
	r92c_init_bb_common(sc);

	rtwn_bb_write(sc, R92C_OFDM0_AGCCORE1(0), 0x69553422);
	rtwn_delay(sc, 1);
	rtwn_bb_write(sc, R92C_OFDM0_AGCCORE1(0), 0x69553420);
	rtwn_delay(sc, 1);

	r88e_crystalcap_write(sc);
}