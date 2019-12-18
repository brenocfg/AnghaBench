#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_pmcrecord {int /*<<< orphan*/  pr_pmcid; } ;
struct pmcstat_pcmap {scalar_t__ ppm_lowpc; scalar_t__ ppm_highpc; struct pmcstat_image* ppm_image; } ;
struct pmcstat_image {scalar_t__ pi_type; scalar_t__ pi_end; scalar_t__ pi_start; int /*<<< orphan*/  pi_gmlist; } ;
struct pmcstat_gmonfile {int pgf_nbuckets; int pgf_ndatabytes; int pgf_overflow; scalar_t__ pgf_nsamples; int /*<<< orphan*/ * pgf_gmondata; int /*<<< orphan*/ * pgf_file; int /*<<< orphan*/  pgf_pmcid; int /*<<< orphan*/  pgf_name; } ;
struct gmonhdr {int dummy; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;
typedef  scalar_t__ WIDEHISTCOUNTER ;
struct TYPE_5__ {int pa_flags; int /*<<< orphan*/  pa_samplesdir; } ;
struct TYPE_4__ {int /*<<< orphan*/  ps_samples_indeterminable; int /*<<< orphan*/  ps_samples_unknown_offset; } ;
typedef  scalar_t__ HISTCOUNTER ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int FLAG_DO_WIDE_GPROF_HC ; 
 scalar_t__ FUNCTION_ALIGNMENT ; 
 scalar_t__ HISTCOUNTER_MAX ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmcstat_gmonfile*,int /*<<< orphan*/ ) ; 
 scalar_t__ PMCSTAT_IMAGE_INDETERMINABLE ; 
 scalar_t__ PMCSTAT_IMAGE_UNKNOWN ; 
 scalar_t__ WIDEHISTCOUNTER_MAX ; 
 TYPE_2__ args ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pmcstat_gmonfile* calloc (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int hc_sz ; 
 int howmany (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pgf_next ; 
 int /*<<< orphan*/  pmcstat_gmon_create_file (struct pmcstat_gmonfile*,struct pmcstat_image*) ; 
 int /*<<< orphan*/  pmcstat_gmon_create_name (int /*<<< orphan*/ ,struct pmcstat_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_gmon_map_file (struct pmcstat_gmonfile*) ; 
 int /*<<< orphan*/  pmcstat_image_determine_type (struct pmcstat_image*,TYPE_2__*) ; 
 struct pmcstat_gmonfile* pmcstat_image_find_gmonfile (struct pmcstat_image*,int /*<<< orphan*/ ) ; 
 struct pmcstat_process* pmcstat_kernproc ; 
 struct pmcstat_pcmap* pmcstat_process_find_map (struct pmcstat_process*,scalar_t__) ; 
 TYPE_1__ pmcstat_stats ; 

void
pmcpl_gmon_process(struct pmcstat_process *pp, struct pmcstat_pmcrecord *pmcr,
    uint32_t nsamples, uintfptr_t *cc, int usermode, uint32_t cpu)
{
	struct pmcstat_pcmap *map;
	struct pmcstat_image *image;
	struct pmcstat_gmonfile *pgf;
	uintfptr_t bucket;
	HISTCOUNTER *hc;
	WIDEHISTCOUNTER *whc;
	pmc_id_t pmcid;

	(void) nsamples; (void) usermode; (void) cpu;

	map = pmcstat_process_find_map(usermode ? pp : pmcstat_kernproc, cc[0]);
	if (map == NULL) {
		/* Unknown offset. */
		pmcstat_stats.ps_samples_unknown_offset++;
		return;
	}

	assert(cc[0] >= map->ppm_lowpc && cc[0] < map->ppm_highpc);

	image = map->ppm_image;
	pmcid = pmcr->pr_pmcid;

	/*
	 * If this is the first time we are seeing a sample for
	 * this executable image, try determine its parameters.
	 */
	if (image->pi_type == PMCSTAT_IMAGE_UNKNOWN)
		pmcstat_image_determine_type(image, &args);

	assert(image->pi_type != PMCSTAT_IMAGE_UNKNOWN);

	/* Ignore samples in images that we know nothing about. */
	if (image->pi_type == PMCSTAT_IMAGE_INDETERMINABLE) {
		pmcstat_stats.ps_samples_indeterminable++;
		return;
	}

	/*
	 * Find the gmon file corresponding to 'pmcid', creating it if
	 * needed.
	 */
	pgf = pmcstat_image_find_gmonfile(image, pmcid);
	if (pgf == NULL) {
		if (hc_sz == 0) {
			/* Determine the correct histcounter size. */
			if (args.pa_flags & FLAG_DO_WIDE_GPROF_HC)
				hc_sz = sizeof(WIDEHISTCOUNTER);
			else
				hc_sz = sizeof(HISTCOUNTER);
		}

		if ((pgf = calloc(1, sizeof(*pgf))) == NULL)
			err(EX_OSERR, "ERROR:");

		pgf->pgf_gmondata = NULL;	/* mark as unmapped */
		pgf->pgf_name = pmcstat_gmon_create_name(args.pa_samplesdir,
		    image, pmcid);
		pgf->pgf_pmcid = pmcid;
		assert(image->pi_end > image->pi_start);
		pgf->pgf_nbuckets = howmany(image->pi_end - image->pi_start,
		    FUNCTION_ALIGNMENT);	/* see <machine/profile.h> */
		pgf->pgf_ndatabytes = sizeof(struct gmonhdr) +
		    pgf->pgf_nbuckets * hc_sz;
		pgf->pgf_nsamples = 0;
		pgf->pgf_file = NULL;

		pmcstat_gmon_create_file(pgf, image);

		LIST_INSERT_HEAD(&image->pi_gmlist, pgf, pgf_next);
	}

	/*
	 * Map the gmon file in if needed.  It may have been mapped
	 * out under memory pressure.
	 */
	if (pgf->pgf_gmondata == NULL)
		pmcstat_gmon_map_file(pgf);

	assert(pgf->pgf_gmondata != NULL);

	/*
	 *
	 */

	bucket = (cc[0] - map->ppm_lowpc) / FUNCTION_ALIGNMENT;

	assert(bucket < pgf->pgf_nbuckets);

	if (args.pa_flags & FLAG_DO_WIDE_GPROF_HC) {
		whc = (WIDEHISTCOUNTER *) ((uintptr_t) pgf->pgf_gmondata +
		    sizeof(struct gmonhdr));

		/* saturating add */
		if (whc[bucket] < WIDEHISTCOUNTER_MAX)
			whc[bucket]++;
		else /* mark that an overflow occurred */
			pgf->pgf_overflow = 1;
	} else {
		hc = (HISTCOUNTER *) ((uintptr_t) pgf->pgf_gmondata +
		    sizeof(struct gmonhdr));

		/* saturating add */
		if (hc[bucket] < HISTCOUNTER_MAX)
			hc[bucket]++;
		else /* mark that an overflow occurred */
			pgf->pgf_overflow = 1;
	}

	pgf->pgf_nsamples++;
}