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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  ans ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  maybe_warnx (char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static int
check_outfile(const char *outfile)
{
	struct stat sb;
	int ok = 1;

	if (lflag == 0 && stat(outfile, &sb) == 0) {
		if (fflag)
			unlink(outfile);
		else if (isatty(STDIN_FILENO)) {
			char ans[10] = { 'n', '\0' };	/* default */

			fprintf(stderr, "%s already exists -- do you wish to "
					"overwrite (y or n)? " , outfile);
			(void)fgets(ans, sizeof(ans) - 1, stdin);
			if (ans[0] != 'y' && ans[0] != 'Y') {
				fprintf(stderr, "\tnot overwriting\n");
				ok = 0;
			} else
				unlink(outfile);
		} else {
			maybe_warnx("%s already exists -- skipping", outfile);
			ok = 0;
		}
	}
	return ok;
}