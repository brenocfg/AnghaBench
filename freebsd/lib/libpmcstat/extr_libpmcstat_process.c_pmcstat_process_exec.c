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
typedef  int /*<<< orphan*/  uintfptr_t ;
struct pmcstat_stats {int /*<<< orphan*/  ps_exec_indeterminable; int /*<<< orphan*/  ps_exec_aout; int /*<<< orphan*/  ps_exec_elf; int /*<<< orphan*/  ps_exec_errors; } ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_image {int pi_type; } ;
struct pmcstat_args {int dummy; } ;
struct pmc_plugins {int dummy; } ;
typedef  int /*<<< orphan*/  pmcstat_interned_string ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
#define  PMCSTAT_IMAGE_AOUT 131 
#define  PMCSTAT_IMAGE_ELF32 130 
#define  PMCSTAT_IMAGE_ELF64 129 
#define  PMCSTAT_IMAGE_INDETERMINABLE 128 
 int PMCSTAT_IMAGE_UNKNOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_image_determine_type (struct pmcstat_image*,struct pmcstat_args*) ; 
 struct pmcstat_image* pmcstat_image_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmcstat_args*,struct pmc_plugins*) ; 
 int /*<<< orphan*/  pmcstat_process_aout_exec (struct pmcstat_process*,struct pmcstat_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_process_elf_exec (struct pmcstat_process*,struct pmcstat_image*,int /*<<< orphan*/ ,struct pmcstat_args*,struct pmc_plugins*,struct pmcstat_stats*) ; 
 int /*<<< orphan*/  pmcstat_string_unintern (int /*<<< orphan*/ ) ; 

void
pmcstat_process_exec(struct pmcstat_process *pp,
    pmcstat_interned_string path, uintfptr_t entryaddr,
    struct pmcstat_args *args, struct pmc_plugins *plugins,
    struct pmcstat_stats *pmcstat_stats)
{
	struct pmcstat_image *image;

	if ((image = pmcstat_image_from_path(path, 0,
	    args, plugins)) == NULL) {
		pmcstat_stats->ps_exec_errors++;
		return;
	}

	if (image->pi_type == PMCSTAT_IMAGE_UNKNOWN)
		pmcstat_image_determine_type(image, args);

	assert(image->pi_type != PMCSTAT_IMAGE_UNKNOWN);

	switch (image->pi_type) {
	case PMCSTAT_IMAGE_ELF32:
	case PMCSTAT_IMAGE_ELF64:
		pmcstat_stats->ps_exec_elf++;
		pmcstat_process_elf_exec(pp, image, entryaddr,
		    args, plugins, pmcstat_stats);
		break;

	case PMCSTAT_IMAGE_AOUT:
		pmcstat_stats->ps_exec_aout++;
		pmcstat_process_aout_exec(pp, image, entryaddr);
		break;

	case PMCSTAT_IMAGE_INDETERMINABLE:
		pmcstat_stats->ps_exec_indeterminable++;
		break;

	default:
		err(EX_SOFTWARE,
		    "ERROR: Unsupported executable type for \"%s\"",
		    pmcstat_string_unintern(path));
	}
}