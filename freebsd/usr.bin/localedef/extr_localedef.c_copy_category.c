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
typedef  int /*<<< orphan*/  srcpath ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd ; 
 int /*<<< orphan*/  category_file () ; 
 char* category_name () ; 
 int /*<<< orphan*/  dirname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ link (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int verbose ; 

void
copy_category(char *src)
{
	char	srcpath[PATH_MAX];
	int	rv;

	(void) snprintf(srcpath, sizeof (srcpath), "%s/%s",
	    src, category_name());
	rv = access(srcpath, R_OK);
	if ((rv != 0) && (strchr(srcpath, '/') == NULL)) {
		/* Maybe we should try the system locale */
		(void) snprintf(srcpath, sizeof (srcpath),
		    "/usr/lib/locale/%s/%s", src, category_name());
		rv = access(srcpath, R_OK);
	}

	if (rv != 0) {
		fprintf(stderr,"source locale data unavailable: %s", src);
		return;
	}

	if (verbose > 1) {
		(void) printf("Copying category %s from %s: ",
		    category_name(), src);
		(void) fflush(stdout);
	}

	/* make the parent directory */
	if (!bsd)
		(void) mkdir(dirname(category_file()), 0755);

	if (link(srcpath, category_file()) != 0) {
		fprintf(stderr,"unable to copy locale data: %s",
			strerror(errno));
		return;
	}
	if (verbose > 1) {
		(void) printf("done.\n");
	}
}