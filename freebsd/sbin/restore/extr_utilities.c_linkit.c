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
struct stat {scalar_t__ st_flags; } ;

/* Variables and functions */
 int FAIL ; 
 int GOOD ; 
 int HARDLINK ; 
 int /*<<< orphan*/  Nflag ; 
 int SYMLINK ; 
 int /*<<< orphan*/  chflags (char*,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int link (char*,char*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ symlink (char*,char*) ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

int
linkit(char *existing, char *new, int type)
{

	/* if we want to unlink first, do it now so *link() won't fail */
	if (uflag && !Nflag)
		(void)unlink(new);

	if (type == SYMLINK) {
		if (!Nflag && symlink(existing, new) < 0) {
			fprintf(stderr,
			    "warning: cannot create symbolic link %s->%s: %s\n",
			    new, existing, strerror(errno));
			return (FAIL);
		}
	} else if (type == HARDLINK) {
		int ret;

		if (!Nflag && (ret = link(existing, new)) < 0) {
			struct stat s;

			/*
			 * Most likely, the schg flag is set.  Clear the
			 * flags and try again.
			 */
			if (stat(existing, &s) == 0 && s.st_flags != 0 &&
			    chflags(existing, 0) == 0) {
				ret = link(existing, new);
				chflags(existing, s.st_flags);
			}
			if (ret < 0) {
				fprintf(stderr, "warning: cannot create "
				    "hard link %s->%s: %s\n",
				    new, existing, strerror(errno));
				return (FAIL);
			}
		}
	} else {
		panic("linkit: unknown type %d\n", type);
		return (FAIL);
	}
	vprintf(stdout, "Create %s link %s->%s\n",
		type == SYMLINK ? "symbolic" : "hard", new, existing);
	return (GOOD);
}