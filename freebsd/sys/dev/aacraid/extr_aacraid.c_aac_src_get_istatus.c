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
 int AAC_DB_SYNC_COMMAND ; 
 int AAC_MEM0_GETREG4 (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int AAC_MSI_SYNC_STATUS ; 
 int /*<<< orphan*/  AAC_SRC_ODBR_MSI ; 
 int /*<<< orphan*/  AAC_SRC_ODBR_R ; 
 int AAC_SRC_ODR_SHIFT ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_src_get_istatus(struct aac_softc *sc)
{
	int val;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if (sc->msi_enabled) {
		val = AAC_MEM0_GETREG4(sc, AAC_SRC_ODBR_MSI);
		if (val & AAC_MSI_SYNC_STATUS)
			val = AAC_DB_SYNC_COMMAND;
		else
			val = 0;
	} else {
		val = AAC_MEM0_GETREG4(sc, AAC_SRC_ODBR_R) >> AAC_SRC_ODR_SHIFT;
	}
	return(val);
}