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
typedef  int uint64_t ;
struct amdvi_softc {int /*<<< orphan*/  cmp_data; } ;
struct amdvi_cmd {int word0; int word1; int addr; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDVI_CMP_WAIT_OPCODE ; 
 int AMDVI_CMP_WAIT_STORE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct amdvi_cmd* amdvi_get_cmd_tail (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_update_cmd_tail (struct amdvi_softc*) ; 
 int vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
amdvi_cmd_cmp(struct amdvi_softc *softc, const uint64_t data)
{
	struct amdvi_cmd *cmd;
	uint64_t pa;

	cmd = amdvi_get_cmd_tail(softc);
	KASSERT(cmd != NULL, ("Cmd is NULL"));

	pa = vtophys(&softc->cmp_data);
	cmd->opcode = AMDVI_CMP_WAIT_OPCODE;
	cmd->word0 = (pa & 0xFFFFFFF8) |
	    (AMDVI_CMP_WAIT_STORE);
	//(AMDVI_CMP_WAIT_FLUSH | AMDVI_CMP_WAIT_STORE);
	cmd->word1 = (pa >> 32) & 0xFFFFF;
	cmd->addr = data;

	amdvi_update_cmd_tail(softc);
}