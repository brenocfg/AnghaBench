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
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R88E_RF_T_METER ; 
 int /*<<< orphan*/  R88E_RF_T_METER_VAL ; 
 int /*<<< orphan*/  rtwn_rf_read (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t
r88e_temp_read(struct rtwn_softc *sc)
{
	return (MS(rtwn_rf_read(sc, 0, R88E_RF_T_METER),
	    R88E_RF_T_METER_VAL));
}