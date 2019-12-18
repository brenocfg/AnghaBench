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
 int /*<<< orphan*/  R88E_RF_T_METER ; 
 int /*<<< orphan*/  R88E_RF_T_METER_START ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r88e_temp_measure(struct rtwn_softc *sc)
{
	rtwn_rf_write(sc, 0, R88E_RF_T_METER, R88E_RF_T_METER_START);
}