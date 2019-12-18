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
typedef  int uint32_t ;
struct bwi_softc {int dummy; } ;
struct bwi_regwin {int dummy; } ;

/* Variables and functions */
 int BWI_DBG_ATTACH ; 
 int BWI_DBG_INIT ; 
 int /*<<< orphan*/  BWI_STATE_LO ; 
 int BWI_STATE_LO_CLOCK ; 
 int BWI_STATE_LO_RESET ; 
 int CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int,char*,int /*<<< orphan*/ ) ; 
 int bwi_regwin_disable_bits (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_regwin_name (struct bwi_regwin*) ; 

int
bwi_regwin_is_enabled(struct bwi_softc *sc, struct bwi_regwin *rw)
{
	uint32_t val, disable_bits;

	disable_bits = bwi_regwin_disable_bits(sc);
	val = CSR_READ_4(sc, BWI_STATE_LO);

	if ((val & (BWI_STATE_LO_CLOCK |
		    BWI_STATE_LO_RESET |
		    disable_bits)) == BWI_STATE_LO_CLOCK) {
		DPRINTF(sc, BWI_DBG_ATTACH | BWI_DBG_INIT, "%s is enabled\n",
			bwi_regwin_name(rw));
		return 1;
	} else {
		DPRINTF(sc, BWI_DBG_ATTACH | BWI_DBG_INIT, "%s is disabled\n",
			bwi_regwin_name(rw));
		return 0;
	}
}