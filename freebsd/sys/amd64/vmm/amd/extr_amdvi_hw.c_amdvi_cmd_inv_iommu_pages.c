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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct amdvi_softc {int dummy; } ;
struct amdvi_cmd {int /*<<< orphan*/  addr; int /*<<< orphan*/  word1; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDVI_INVD_PAGE_OPCODE ; 
 int /*<<< orphan*/  AMDVI_INVD_PAGE_PDE ; 
 int /*<<< orphan*/  AMDVI_INVD_PAGE_S ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct amdvi_cmd* amdvi_get_cmd_tail (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_update_cmd_tail (struct amdvi_softc*) ; 

__attribute__((used)) static void
amdvi_cmd_inv_iommu_pages(struct amdvi_softc *softc, uint16_t domain_id,
			  uint64_t addr, bool guest_nested,
			  bool pde, bool page)
{
	struct amdvi_cmd *cmd;

	cmd = amdvi_get_cmd_tail(softc);
	KASSERT(cmd != NULL, ("Cmd is NULL"));


	cmd->opcode = AMDVI_INVD_PAGE_OPCODE;
	cmd->word1 = domain_id;
	/*
	 * Invalidate all addresses for this domain.
	 */
	cmd->addr = addr;
	cmd->addr |= pde ? AMDVI_INVD_PAGE_PDE : 0;
	cmd->addr |= page ? AMDVI_INVD_PAGE_S : 0;

	amdvi_update_cmd_tail(softc);
}