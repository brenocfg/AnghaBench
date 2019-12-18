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
typedef  int /*<<< orphan*/  tmpl ;
struct stat {int st_mode; int st_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int MAXPATHLEN ; 
 int NOCHANGEBITS ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  chflags (char const*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/ * quiet_mktemp (char*) ; 
 int rename (char*,char const*) ; 
 int rmdir (char const*) ; 
 scalar_t__ safecopy ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int symlink (char const*,char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
do_symlink(const char *from_name, const char *to_name,
    const struct stat *target_sb)
{
	char tmpl[MAXPATHLEN];

	if (safecopy && target_sb != NULL) {
		(void)snprintf(tmpl, sizeof(tmpl), "%s.inst.XXXXXX", to_name);
		/* This usage is safe. */
		if (quiet_mktemp(tmpl) == NULL)
			err(EX_OSERR, "%s: mktemp", tmpl);

		if (symlink(from_name, tmpl) == -1)
			err(EX_OSERR, "symlink %s -> %s", from_name, tmpl);

		if (target_sb->st_mode & S_IFDIR && rmdir(to_name) == -1) {
			(void)unlink(tmpl);
			err(EX_OSERR, "%s", to_name);
		}
#if HAVE_STRUCT_STAT_ST_FLAGS
		if (target_sb->st_flags & NOCHANGEBITS)
			(void)chflags(to_name, target_sb->st_flags &
			     ~NOCHANGEBITS);
#endif
		if (verbose)
			printf("install: symlink %s -> %s\n",
			    from_name, to_name);
		if (rename(tmpl, to_name) == -1) {
			/* Remove temporary link before exiting. */
			(void)unlink(tmpl);
			err(EX_OSERR, "%s: rename", to_name);
		}
	} else {
		if (verbose)
			printf("install: symlink %s -> %s\n",
			    from_name, to_name);
		if (symlink(from_name, to_name) == -1)
			err(EX_OSERR, "symlink %s -> %s", from_name, to_name);
	}
}