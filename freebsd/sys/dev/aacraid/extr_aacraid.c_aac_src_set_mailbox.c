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
typedef  int /*<<< orphan*/  u_int32_t ;
struct aac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_MEM0_SETREG4 (struct aac_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ AAC_SRC_MAILBOX ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static void
aac_src_set_mailbox(struct aac_softc *sc, u_int32_t command, u_int32_t arg0,
		    u_int32_t arg1, u_int32_t arg2, u_int32_t arg3)
{
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	AAC_MEM0_SETREG4(sc, AAC_SRC_MAILBOX, command);
	AAC_MEM0_SETREG4(sc, AAC_SRC_MAILBOX + 4, arg0);
	AAC_MEM0_SETREG4(sc, AAC_SRC_MAILBOX + 8, arg1);
	AAC_MEM0_SETREG4(sc, AAC_SRC_MAILBOX + 12, arg2);
	AAC_MEM0_SETREG4(sc, AAC_SRC_MAILBOX + 16, arg3);
}