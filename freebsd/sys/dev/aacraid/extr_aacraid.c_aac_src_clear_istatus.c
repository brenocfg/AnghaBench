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
struct aac_softc {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ACCESS_DEVREG (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAC_CLEAR_SYNC_BIT ; 
 int AAC_DB_SYNC_COMMAND ; 
 int /*<<< orphan*/  AAC_MEM0_SETREG4 (struct aac_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAC_SRC_ODBR_C ; 
 int AAC_SRC_ODR_SHIFT ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static void
aac_src_clear_istatus(struct aac_softc *sc, int mask)
{
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if (sc->msi_enabled) {
		if (mask == AAC_DB_SYNC_COMMAND)
			AAC_ACCESS_DEVREG(sc, AAC_CLEAR_SYNC_BIT);
	} else {
		AAC_MEM0_SETREG4(sc, AAC_SRC_ODBR_C, mask << AAC_SRC_ODR_SHIFT);
	}
}