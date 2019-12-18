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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_OFDM0_AGCCORE1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_OFDM0_AGCCORE1_GAIN_M ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r88e_set_gain(struct rtwn_softc *sc, uint8_t gain)
{

	rtwn_bb_setbits(sc, R92C_OFDM0_AGCCORE1(0),
	    R92C_OFDM0_AGCCORE1_GAIN_M, gain);
}