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
struct rtwn_softc {char* name; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int chip; scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ R92C_BOARD_TYPE_HIGHPA ; 
 scalar_t__ R92C_BOARD_TYPE_MINICARD ; 
 int R92C_CHIP_92C ; 

__attribute__((used)) static void
r92cu_set_name(struct rtwn_softc *sc, uint8_t *buf)
{
	struct r92c_softc *rs = sc->sc_priv;

	if (!(rs->chip & R92C_CHIP_92C)) {
		if (rs->board_type == R92C_BOARD_TYPE_HIGHPA)
			sc->name = "RTL8188RU";
		else if (rs->board_type == R92C_BOARD_TYPE_MINICARD)
			sc->name = "RTL8188CU-VAU";
		else
			sc->name = "RTL8188CUS";
	} else
		sc->name = "RTL8192CU";
}