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
struct of_drconf_cell_v2 {void* flags; void* aa_index; void* drc_index; int /*<<< orphan*/  base_addr; } ;
struct drmem_lmb {int /*<<< orphan*/  aa_index; int /*<<< orphan*/  drc_index; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drmem_lmb_flags (struct drmem_lmb*) ; 

__attribute__((used)) static void init_drconf_v2_cell(struct of_drconf_cell_v2 *dr_cell,
				struct drmem_lmb *lmb)
{
	dr_cell->base_addr = cpu_to_be64(lmb->base_addr);
	dr_cell->drc_index = cpu_to_be32(lmb->drc_index);
	dr_cell->aa_index = cpu_to_be32(lmb->aa_index);
	dr_cell->flags = cpu_to_be32(drmem_lmb_flags(lmb));
}