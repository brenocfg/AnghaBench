#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
struct pmcstat_image {int /*<<< orphan*/ * pi_addr2line; int /*<<< orphan*/  pi_fullpath; } ;
typedef  int /*<<< orphan*/  imagepath ;
typedef  int /*<<< orphan*/  cmdline ;
struct TYPE_2__ {char* pa_fsroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 TYPE_1__ args ; 
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,void*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pmcstat_image_addr2line(struct pmcstat_image *image, uintfptr_t addr,
    char *sourcefile, size_t sourcefile_len, unsigned *sourceline,
    char *funcname, size_t funcname_len)
{
	static int addr2line_warn = 0;

	char *sep, cmdline[PATH_MAX], imagepath[PATH_MAX];
	unsigned l;
	int fd;

	if (image->pi_addr2line == NULL) {
		/* Try default debug file location. */
		snprintf(imagepath, sizeof(imagepath),
		    "/usr/lib/debug/%s%s.debug",
		    args.pa_fsroot,
		    pmcstat_string_unintern(image->pi_fullpath));
		fd = open(imagepath, O_RDONLY);
		if (fd < 0) {
			/* Old kernel symbol path. */
			snprintf(imagepath, sizeof(imagepath), "%s%s.symbols",
			    args.pa_fsroot,
			    pmcstat_string_unintern(image->pi_fullpath));
			fd = open(imagepath, O_RDONLY);
			if (fd < 0) {
				snprintf(imagepath, sizeof(imagepath), "%s%s",
				    args.pa_fsroot,
				    pmcstat_string_unintern(
				        image->pi_fullpath));
			}
		}
		if (fd >= 0)
			close(fd);
		/*
		 * New addr2line support recursive inline function with -i
		 * but the format does not add a marker when no more entries
		 * are available.
		 */
		snprintf(cmdline, sizeof(cmdline), "addr2line -Cfe \"%s\"",
		    imagepath);
		image->pi_addr2line = popen(cmdline, "r+");
		if (image->pi_addr2line == NULL) {
			if (!addr2line_warn) {
				addr2line_warn = 1;
				warnx(
"WARNING: addr2line is needed for source code information."
				    );
			}
			return (0);
		}
	}

	if (feof(image->pi_addr2line) || ferror(image->pi_addr2line)) {
		warnx("WARNING: addr2line pipe error");
		pclose(image->pi_addr2line);
		image->pi_addr2line = NULL;
		return (0);
	}

	fprintf(image->pi_addr2line, "%p\n", (void *)addr);

	if (fgets(funcname, funcname_len, image->pi_addr2line) == NULL) {
		warnx("WARNING: addr2line function name read error");
		return (0);
	}
	sep = strchr(funcname, '\n');
	if (sep != NULL)
		*sep = '\0';

	if (fgets(sourcefile, sourcefile_len, image->pi_addr2line) == NULL) {
		warnx("WARNING: addr2line source file read error");
		return (0);
	}
	sep = strchr(sourcefile, ':');
	if (sep == NULL) {
		warnx("WARNING: addr2line source line separator missing");
		return (0);
	}
	*sep = '\0';
	l = atoi(sep+1);
	if (l == 0)
		return (0);
	*sourceline = l;
	return (1);
}