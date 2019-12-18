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
typedef  int /*<<< orphan*/  uint32_t ;
struct rawarc {int /*<<< orphan*/  raw_count; scalar_t__ raw_selfpc; scalar_t__ raw_frompc; } ;
struct pmcstat_image {scalar_t__ pi_vaddr; } ;
struct pmcstat_gmonfile {int /*<<< orphan*/ * pgf_file; int /*<<< orphan*/  pgf_name; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;
typedef  int /*<<< orphan*/  arc ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (struct rawarc*,int,int,int /*<<< orphan*/ *) ; 
 struct pmcstat_gmonfile* pmcstat_image_find_gmonfile (struct pmcstat_image*,int /*<<< orphan*/ ) ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmcstat_gmon_append_arc(struct pmcstat_image *image, pmc_id_t pmcid,
    uintptr_t rawfrom, uintptr_t rawto, uint32_t count)
{
	struct rawarc arc;	/* from <sys/gmon.h> */
	const char *pathname;
	struct pmcstat_gmonfile *pgf;

	if ((pgf = pmcstat_image_find_gmonfile(image, pmcid)) == NULL)
		return;

	if (pgf->pgf_file == NULL) {
		pathname = pmcstat_string_unintern(pgf->pgf_name);
		if ((pgf->pgf_file = fopen(pathname, "a")) == NULL)
			return;
	}

	arc.raw_frompc = rawfrom + image->pi_vaddr;
	arc.raw_selfpc = rawto + image->pi_vaddr;
	arc.raw_count = count;

	(void) fwrite(&arc, sizeof(arc), 1, pgf->pgf_file);

}