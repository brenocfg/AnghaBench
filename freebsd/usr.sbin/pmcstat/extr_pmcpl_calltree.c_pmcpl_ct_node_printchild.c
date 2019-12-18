#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
struct pmcpl_ct_node {int pct_narc; scalar_t__ pct_type; TYPE_2__* pct_arc; TYPE_1__* pct_sym; TYPE_3__* pct_image; int /*<<< orphan*/  pct_ifn; int /*<<< orphan*/  pct_ifl; scalar_t__ pct_func; } ;
typedef  int /*<<< orphan*/  sourcefile ;
typedef  int /*<<< orphan*/  funcname ;
struct TYPE_8__ {int /*<<< orphan*/  pa_graphfile; } ;
struct TYPE_7__ {scalar_t__ pi_vaddr; int /*<<< orphan*/  pi_fullpath; } ;
struct TYPE_6__ {int pcta_call; int /*<<< orphan*/  pcta_samples; struct pmcpl_ct_node* pcta_child; } ;
struct TYPE_5__ {int /*<<< orphan*/  ps_name; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int PMCPL_CT_SAMPLE (int,int /*<<< orphan*/ *) ; 
 scalar_t__ PMCPL_PCT_NAME ; 
 TYPE_4__ args ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pmcstat_image_addr2line (TYPE_3__*,scalar_t__,char*,int,int*,char*,int) ; 
 int pmcstat_npmcs ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmcpl_ct_node_printchild(struct pmcpl_ct_node *ct, uintfptr_t paddr,
    int pline)
{
	int i, j, line;
	uintfptr_t addr;
	struct pmcpl_ct_node *child;
	char sourcefile[PATH_MAX];
	char funcname[PATH_MAX];

	/*
	 * Child cost.
	 * TODO: attach child cost to the real position in the function.
	 * TODO: cfn=<fn> / call <ncall> addr(<fn>) / addr(call <fn>) <arccost>
	 */
	for (i=0 ; i<ct->pct_narc; i++) {
		child = ct->pct_arc[i].pcta_child;
		/* Object binary. */
		fprintf(args.pa_graphfile, "cob=%s\n",
		    pmcstat_string_unintern(child->pct_image->pi_fullpath));
		/* Child function name. */
		addr = child->pct_image->pi_vaddr + child->pct_func;
		line = 0;
		/* Child function source file. */
		if (child->pct_type == PMCPL_PCT_NAME) {
			fprintf(args.pa_graphfile, "cfi=%s\ncfn=%s\n",
			    pmcstat_string_unintern(child->pct_ifl),
			    pmcstat_string_unintern(child->pct_ifn));
		} else if (pmcstat_image_addr2line(child->pct_image, addr,
		    sourcefile, sizeof(sourcefile), &line,
		    funcname, sizeof(funcname))) {
			fprintf(args.pa_graphfile, "cfi=%s\ncfn=%s\n",
				sourcefile, funcname);
		} else {
			if (child->pct_sym != NULL)
				fprintf(args.pa_graphfile,
				    "cfi=???\ncfn=%s\n",
				    pmcstat_string_unintern(
				        child->pct_sym->ps_name));
			else
				fprintf(args.pa_graphfile,
				    "cfi=???\ncfn=%p\n", (void *)addr);
		}

		/* Child function address, line and call count. */
		fprintf(args.pa_graphfile, "calls=%u %p %u\n",
		    ct->pct_arc[i].pcta_call, (void *)addr, line);

		/*
		 * Call address, line, sample.
		 * TODO: Associate call address to the right location.
		 */
		fprintf(args.pa_graphfile, "%p %u", (void *)paddr, pline);
		for (j = 0; j<pmcstat_npmcs; j++)
			fprintf(args.pa_graphfile, " %u",
			    PMCPL_CT_SAMPLE(j, &ct->pct_arc[i].pcta_samples));
		fprintf(args.pa_graphfile, "\n");
	}
}