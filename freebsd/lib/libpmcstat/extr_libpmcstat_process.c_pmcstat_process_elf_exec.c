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
typedef  scalar_t__ uintmax_t ;
typedef  scalar_t__ uintfptr_t ;
struct pmcstat_stats {int /*<<< orphan*/  ps_exec_errors; } ;
struct pmcstat_process {int dummy; } ;
struct pmcstat_image {scalar_t__ pi_type; scalar_t__ pi_entry; int /*<<< orphan*/  pi_dynlinkerpath; scalar_t__ pi_isdynamic; scalar_t__ pi_vaddr; } ;
struct pmcstat_args {int dummy; } ;
struct pmc_plugins {int dummy; } ;

/* Variables and functions */
 scalar_t__ PMCSTAT_IMAGE_ELF32 ; 
 scalar_t__ PMCSTAT_IMAGE_ELF64 ; 
 scalar_t__ PMCSTAT_IMAGE_UNKNOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pmcstat_image* pmcstat_image_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmcstat_args*,struct pmc_plugins*) ; 
 int /*<<< orphan*/  pmcstat_image_get_elf_params (struct pmcstat_image*,struct pmcstat_args*) ; 
 int /*<<< orphan*/  pmcstat_image_link (struct pmcstat_process*,struct pmcstat_image*,scalar_t__) ; 
 int /*<<< orphan*/  pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

void
pmcstat_process_elf_exec(struct pmcstat_process *pp,
    struct pmcstat_image *image, uintfptr_t entryaddr,
    struct pmcstat_args *args, struct pmc_plugins *plugins,
    struct pmcstat_stats *pmcstat_stats)
{
	uintmax_t libstart;
	struct pmcstat_image *rtldimage;

	assert(image->pi_type == PMCSTAT_IMAGE_ELF32 ||
	    image->pi_type == PMCSTAT_IMAGE_ELF64);

	/* Create a map entry for the base executable. */
	pmcstat_image_link(pp, image, image->pi_vaddr);

	/*
	 * For dynamically linked executables we need to determine
	 * where the dynamic linker was mapped to for this process,
	 * Subsequent executable objects that are mapped in by the
	 * dynamic linker will be tracked by log events of type
	 * PMCLOG_TYPE_MAP_IN.
	 */

	if (image->pi_isdynamic) {

		/*
		 * The runtime loader gets loaded just after the maximum
		 * possible heap address.  Like so:
		 *
		 * [  TEXT DATA BSS HEAP -->*RTLD  SHLIBS   <--STACK]
		 * ^					            ^
		 * 0				   VM_MAXUSER_ADDRESS

		 *
		 * The exact address where the loader gets mapped in
		 * will vary according to the size of the executable
		 * and the limits on the size of the process'es data
		 * segment at the time of exec().  The entry address
		 * recorded at process exec time corresponds to the
		 * 'start' address inside the dynamic linker.  From
		 * this we can figure out the address where the
		 * runtime loader's file object had been mapped to.
		 */
		rtldimage = pmcstat_image_from_path(image->pi_dynlinkerpath,
		    0, args, plugins);
		if (rtldimage == NULL) {
			warnx("WARNING: Cannot find image for \"%s\".",
			    pmcstat_string_unintern(image->pi_dynlinkerpath));
			pmcstat_stats->ps_exec_errors++;
			return;
		}

		if (rtldimage->pi_type == PMCSTAT_IMAGE_UNKNOWN)
			pmcstat_image_get_elf_params(rtldimage, args);

		if (rtldimage->pi_type != PMCSTAT_IMAGE_ELF32 &&
		    rtldimage->pi_type != PMCSTAT_IMAGE_ELF64) {
			warnx("WARNING: rtld not an ELF object \"%s\".",
			    pmcstat_string_unintern(image->pi_dynlinkerpath));
			return;
		}

		libstart = entryaddr - rtldimage->pi_entry;
		pmcstat_image_link(pp, rtldimage, libstart);
	}
}