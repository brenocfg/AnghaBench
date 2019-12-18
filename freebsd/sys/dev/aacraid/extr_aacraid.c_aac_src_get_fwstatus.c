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
struct aac_softc {int dummy; } ;

/* Variables and functions */
 int AAC_MEM0_GETREG4 (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAC_SRC_OMR ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_src_get_fwstatus(struct aac_softc *sc)
{
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	return(AAC_MEM0_GETREG4(sc, AAC_SRC_OMR));
}