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
 int AAC_MEM1_GETREG4 (struct aac_softc*,scalar_t__) ; 
 scalar_t__ AAC_RKT_MAILBOX ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_rkt_get_mailbox(struct aac_softc *sc, int mb)
{
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	return(AAC_MEM1_GETREG4(sc, AAC_RKT_MAILBOX + (mb * 4)));
}