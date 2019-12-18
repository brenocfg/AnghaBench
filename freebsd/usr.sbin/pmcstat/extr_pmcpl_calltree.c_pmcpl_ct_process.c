#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
typedef  scalar_t__ uint32_t ;
struct pmcstat_symbol {scalar_t__ ps_start; } ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_pmcrecord {int pr_pmcin; int /*<<< orphan*/  pr_dubious_frames; } ;
struct pmcstat_pcmap {struct pmcstat_image* ppm_image; scalar_t__ ppm_lowpc; } ;
struct pmcstat_image {scalar_t__ pi_start; scalar_t__ pi_vaddr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sb; } ;
struct pmcpl_ct_node {TYPE_2__ pct_samples; } ;
struct TYPE_7__ {scalar_t__ pa_ctdumpinstr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ps_callchain_dubious_frames; int /*<<< orphan*/  ps_samples_unknown_function; } ;

/* Variables and functions */
 int PMC_CALLCHAIN_DEPTH_MAX ; 
 TYPE_4__ args ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ pmcpl_ct_callid ; 
 int /*<<< orphan*/  pmcpl_ct_instr_add (struct pmcpl_ct_node*,int,scalar_t__,int) ; 
 struct pmcpl_ct_node* pmcpl_ct_node_hash_lookup (struct pmcstat_image*,scalar_t__,struct pmcstat_symbol*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcpl_ct_node_update (struct pmcpl_ct_node*,struct pmcpl_ct_node*,int,int,int) ; 
 struct pmcpl_ct_node* pmcpl_ct_root ; 
 int /*<<< orphan*/  pmcpl_ct_samples_grow (TYPE_2__*) ; 
 struct pmcstat_process* pmcstat_kernproc ; 
 struct pmcstat_pcmap* pmcstat_process_find_map (struct pmcstat_process*,scalar_t__) ; 
 TYPE_1__ pmcstat_stats ; 
 struct pmcstat_symbol* pmcstat_symbol_search (struct pmcstat_image*,scalar_t__) ; 

void
pmcpl_ct_process(struct pmcstat_process *pp, struct pmcstat_pmcrecord *pmcr,
    uint32_t nsamples, uintfptr_t *cc, int usermode, uint32_t cpu)
{
	int i, n, pmcin;
	uintfptr_t pc, loadaddress;
	struct pmcstat_image *image;
	struct pmcstat_symbol *sym;
	struct pmcstat_pcmap *ppm[PMC_CALLCHAIN_DEPTH_MAX];
	struct pmcstat_process *km;
	struct pmcpl_ct_node *ct;
	struct pmcpl_ct_node *ctl[PMC_CALLCHAIN_DEPTH_MAX+1];

	(void) cpu;

	assert(nsamples>0 && nsamples<=PMC_CALLCHAIN_DEPTH_MAX);

	/* Get the PMC index. */
	pmcin = pmcr->pr_pmcin;

	/*
	 * Validate mapping for the callchain.
	 * Go from bottom to first invalid entry.
	 */
	km = pmcstat_kernproc;
	for (n = 0; n < (int)nsamples; n++) {
		ppm[n] = pmcstat_process_find_map(usermode ?
		    pp : km, cc[n]);
		if (ppm[n] == NULL) {
			/* Detect full frame capture (kernel + user). */
			if (!usermode) {
				ppm[n] = pmcstat_process_find_map(pp, cc[n]);
				if (ppm[n] != NULL)
					km = pp;
			}
		}
		if (ppm[n] == NULL)
			break;
	}
	if (n-- == 0) {
		pmcstat_stats.ps_callchain_dubious_frames++;
		pmcr->pr_dubious_frames++;
		return;
	}

	/* Increase the call generation counter. */
	pmcpl_ct_samples_grow(&pmcpl_ct_callid);
	pmcpl_ct_callid.sb[pmcin]++;

	/*
	 * Build node list.
	 */
	ctl[0] = pmcpl_ct_root;
	for (i = 1; n >= 0; n--) {
		image = ppm[n]->ppm_image;
		loadaddress = ppm[n]->ppm_lowpc +
		    image->pi_vaddr - image->pi_start;
		/* Convert to an offset in the image. */
		pc = cc[n] - loadaddress;
		/*
		 * Try determine the function at this offset.  If we can't
		 * find a function round leave the `pc' value alone.
		 */
		if ((sym = pmcstat_symbol_search(image, pc)) != NULL)
			pc = sym->ps_start;
		else
			pmcstat_stats.ps_samples_unknown_function++;

		ct = pmcpl_ct_node_hash_lookup(image, pc, sym, NULL, NULL);
		if (ct == NULL) {
			pmcstat_stats.ps_callchain_dubious_frames++;
			continue;
		}
		ctl[i++] = ct;
	}
	/* No valid node found. */
	if (i == 1)
		return;
	n = i;

	ct = ctl[0];
	for (i = 1; i < n; i++)
		pmcpl_ct_node_update(ctl[i-1], ctl[i], pmcin, 1, 1);

	/*
	 * Increment the sample count for this PMC.
	 */
	pmcpl_ct_samples_grow(&ctl[n-1]->pct_samples);
	ctl[n-1]->pct_samples.sb[pmcin]++;

	/* Update per instruction sample if required. */
	if (args.pa_ctdumpinstr)
		pmcpl_ct_instr_add(ctl[n-1], pmcin, cc[0] -
		    (ppm[0]->ppm_lowpc + ppm[0]->ppm_image->pi_vaddr -
		     ppm[0]->ppm_image->pi_start), 1);
}