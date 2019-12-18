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
typedef  int /*<<< orphan*/  uint16_t ;
struct amdvi_softc {int /*<<< orphan*/  dev; } ;
struct amdvi_cmd {int /*<<< orphan*/  word0; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDVI_INVD_DTE_OPCODE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct amdvi_cmd* amdvi_get_cmd_tail (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_update_cmd_tail (struct amdvi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amdvi_cmd_inv_dte(struct amdvi_softc *softc, uint16_t devid)
{
	struct amdvi_cmd *cmd;

	cmd = amdvi_get_cmd_tail(softc);
	KASSERT(cmd != NULL, ("Cmd is NULL"));
	cmd->opcode = AMDVI_INVD_DTE_OPCODE;
	cmd->word0 = devid;
	amdvi_update_cmd_tail(softc);
#ifdef AMDVI_DEBUG_CMD
	device_printf(softc->dev, "Invalidated DTE:0x%x\n", devid);
#endif
}