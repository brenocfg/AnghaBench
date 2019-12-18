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
typedef  scalar_t__ uint32_t ;
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BWI_BUSREV_0 ; 
 scalar_t__ BWI_BUSREV_1 ; 
 int BWI_DBG_ATTACH ; 
 int BWI_DBG_INIT ; 
 int BWI_DBG_MISC ; 
 int /*<<< orphan*/  BWI_ID_LO ; 
 int /*<<< orphan*/  BWI_ID_LO_BUSREV_MASK ; 
 scalar_t__ BWI_STATE_LO_DISABLE1 ; 
 scalar_t__ BWI_STATE_LO_DISABLE2 ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int,char*,scalar_t__) ; 
 scalar_t__ __SHIFTOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
bwi_regwin_disable_bits(struct bwi_softc *sc)
{
	uint32_t busrev;

	/* XXX cache this */
	busrev = __SHIFTOUT(CSR_READ_4(sc, BWI_ID_LO), BWI_ID_LO_BUSREV_MASK);
	DPRINTF(sc, BWI_DBG_ATTACH | BWI_DBG_INIT | BWI_DBG_MISC,
		"bus rev %u\n", busrev);

	if (busrev == BWI_BUSREV_0)
		return BWI_STATE_LO_DISABLE1;
	else if (busrev == BWI_BUSREV_1)
		return BWI_STATE_LO_DISABLE2;
	else
		return (BWI_STATE_LO_DISABLE1 | BWI_STATE_LO_DISABLE2);
}