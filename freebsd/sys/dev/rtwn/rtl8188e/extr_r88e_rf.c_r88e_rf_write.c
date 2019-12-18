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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88E_LSSI_PARAM_ADDR ; 
 int /*<<< orphan*/  R92C_LSSI_PARAM (int) ; 
 int /*<<< orphan*/  R92C_LSSI_PARAM_DATA ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_write (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r88e_rf_write(struct rtwn_softc *sc, int chain, uint8_t addr, uint32_t val)
{
	rtwn_bb_write(sc, R92C_LSSI_PARAM(chain),
	    SM(R88E_LSSI_PARAM_ADDR, addr) |
	    SM(R92C_LSSI_PARAM_DATA, val));
}