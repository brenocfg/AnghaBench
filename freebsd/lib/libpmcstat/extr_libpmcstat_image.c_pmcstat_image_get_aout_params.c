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
struct pmcstat_image {int /*<<< orphan*/  pi_type; scalar_t__ pi_iskernelmodule; int /*<<< orphan*/  pi_execpath; } ;
struct pmcstat_args {char* pa_fsroot; int pa_verbosity; } ;
struct exec {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ex ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 scalar_t__ N_BADMAG (struct exec) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PMCSTAT_IMAGE_AOUT ; 
 int /*<<< orphan*/  PMCSTAT_IMAGE_INDETERMINABLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,struct exec*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

void
pmcstat_image_get_aout_params(struct pmcstat_image *image,
    struct pmcstat_args *args)
{
	int fd;
	ssize_t nbytes;
	struct exec ex;
	const char *path;
	char buffer[PATH_MAX];

	path = pmcstat_string_unintern(image->pi_execpath);
	assert(path != NULL);

	if (image->pi_iskernelmodule)
		errx(EX_SOFTWARE,
		    "ERROR: a.out kernel modules are unsupported \"%s\"", path);

	(void) snprintf(buffer, sizeof(buffer), "%s%s",
	    args->pa_fsroot, path);

	if ((fd = open(buffer, O_RDONLY, 0)) < 0 ||
	    (nbytes = read(fd, &ex, sizeof(ex))) < 0) {
		if (args->pa_verbosity >= 2)
			warn("WARNING: Cannot determine type of \"%s\"",
			    path);
		image->pi_type = PMCSTAT_IMAGE_INDETERMINABLE;
		if (fd != -1)
			(void) close(fd);
		return;
	}

	(void) close(fd);

	if ((unsigned) nbytes != sizeof(ex) ||
	    N_BADMAG(ex))
		return;

	image->pi_type = PMCSTAT_IMAGE_AOUT;

	/* TODO: the rest of a.out processing */

	return;
}