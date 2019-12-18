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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uintfptr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pmcstat_symbol {scalar_t__ ps_start; scalar_t__ ps_end; int /*<<< orphan*/  ps_name; } ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_pmcrecord {int dummy; } ;
struct pmcstat_pcmap {scalar_t__ ppm_lowpc; scalar_t__ ppm_highpc; struct pmcstat_image* ppm_image; } ;
struct pmcstat_image {scalar_t__ pi_vaddr; scalar_t__ pi_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  pa_graphfile; } ;
struct TYPE_3__ {int /*<<< orphan*/  ps_samples_unknown_offset; } ;

/* Variables and functions */
 TYPE_2__ args ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmcstat_process* pmcstat_kernproc ; 
 struct pmcstat_pcmap* pmcstat_process_find_map (struct pmcstat_process*,scalar_t__) ; 
 TYPE_1__ pmcstat_stats ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 struct pmcstat_symbol* pmcstat_symbol_search (struct pmcstat_image*,scalar_t__) ; 

void
pmcpl_annotate_process(struct pmcstat_process *pp, struct pmcstat_pmcrecord *pmcr,
    uint32_t nsamples, uintfptr_t *cc, int usermode, uint32_t cpu)
{
	struct pmcstat_pcmap *map;
	struct pmcstat_symbol *sym;
	uintfptr_t newpc;
	struct pmcstat_image *image;

	(void) pmcr; (void) nsamples; (void) usermode; (void) cpu;

	map = pmcstat_process_find_map(usermode ? pp : pmcstat_kernproc, cc[0]);
	if (map == NULL) {
		/* Unknown offset. */
		pmcstat_stats.ps_samples_unknown_offset++;
		return;
	}

	assert(cc[0] >= map->ppm_lowpc && cc[0] < map->ppm_highpc);

	image = map->ppm_image;
	newpc = cc[0] - (map->ppm_lowpc +
		(image->pi_vaddr - image->pi_start));
	sym = pmcstat_symbol_search(image, newpc);
	if (sym == NULL)
		return;

	fprintf(args.pa_graphfile, "%p %s 0x%jx 0x%jx\n",
		(void *)cc[0],
		pmcstat_string_unintern(sym->ps_name),
		(uintmax_t)(sym->ps_start +
		image->pi_vaddr), (uintmax_t)(sym->ps_end +
		image->pi_vaddr));
}