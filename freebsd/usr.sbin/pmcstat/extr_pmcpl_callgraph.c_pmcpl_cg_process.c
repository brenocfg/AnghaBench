#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
typedef  size_t uint32_t ;
struct pmcstat_symbol {scalar_t__ ps_start; } ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_pmcrecord {int /*<<< orphan*/  pr_dubious_frames; int /*<<< orphan*/  pr_pmcid; } ;
struct pmcstat_pcmap {scalar_t__ ppm_lowpc; struct pmcstat_image* ppm_image; } ;
struct pmcstat_image {scalar_t__ pi_start; scalar_t__ pi_vaddr; } ;
struct pmcstat_cgnode {int /*<<< orphan*/  pcg_count; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;
struct TYPE_4__ {scalar_t__ pa_graphdepth; } ;
struct TYPE_3__ {int /*<<< orphan*/  ps_callchain_dubious_frames; } ;

/* Variables and functions */
 TYPE_2__ args ; 
 struct pmcstat_cgnode* pmcstat_cgnode_find (struct pmcstat_cgnode*,struct pmcstat_image*,scalar_t__) ; 
 struct pmcstat_cgnode* pmcstat_cgnode_hash_lookup_pc (struct pmcstat_process*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct pmcstat_process* pmcstat_kernproc ; 
 struct pmcstat_pcmap* pmcstat_process_find_map (struct pmcstat_process*,scalar_t__) ; 
 TYPE_1__ pmcstat_stats ; 
 struct pmcstat_symbol* pmcstat_symbol_search (struct pmcstat_image*,scalar_t__) ; 

void
pmcpl_cg_process(struct pmcstat_process *pp, struct pmcstat_pmcrecord *pmcr,
    uint32_t nsamples, uintfptr_t *cc, int usermode, uint32_t cpu)
{
	uintfptr_t pc, loadaddress;
	uint32_t n;
	struct pmcstat_image *image;
	struct pmcstat_pcmap *ppm;
	struct pmcstat_symbol *sym;
	struct pmcstat_cgnode *parent, *child;
	struct pmcstat_process *km;
	pmc_id_t pmcid;

	(void) cpu;

	/*
	 * Find the callgraph node recorded in the global hash table
	 * for this (pmcid, pc).
	 */

	pc = cc[0];
	pmcid = pmcr->pr_pmcid;
	child = parent = pmcstat_cgnode_hash_lookup_pc(pp, pmcid, pc, usermode);
	if (parent == NULL) {
		pmcstat_stats.ps_callchain_dubious_frames++;
		pmcr->pr_dubious_frames++;
		return;
	}

	parent->pcg_count++;

	/*
	 * For each return address in the call chain record, subject
	 * to the maximum depth desired.
	 * - Find the image associated with the sample.  Stop if there
	 *   there is no valid image at that address.
	 * - Find the function that overlaps the return address.
	 * - If found: use the start address of the function.
	 *   If not found (say an object's symbol table is not present or
	 *   is incomplete), round down to th gprof bucket granularity.
	 * - Convert return virtual address to an offset in the image.
	 * - Look for a child with the same {offset,image} tuple,
	 *   inserting one if needed.
	 * - Increment the count of occurrences of the child.
	 */
	km = pmcstat_kernproc;

	for (n = 1; n < (uint32_t) args.pa_graphdepth && n < nsamples; n++,
	    parent = child) {
		pc = cc[n];

		ppm = pmcstat_process_find_map(usermode ? pp : km, pc);
		if (ppm == NULL) {
			/* Detect full frame capture (kernel + user). */
			if (!usermode) {
				ppm = pmcstat_process_find_map(pp, pc);
				if (ppm != NULL)
					km = pp;
			}
		}
		if (ppm == NULL)
			continue;

		image = ppm->ppm_image;
		loadaddress = ppm->ppm_lowpc + image->pi_vaddr -
		    image->pi_start;
		pc -= loadaddress;

		if ((sym = pmcstat_symbol_search(image, pc)) != NULL)
			pc = sym->ps_start;

		child = pmcstat_cgnode_find(parent, image, pc);
		child->pcg_count++;
	}
}