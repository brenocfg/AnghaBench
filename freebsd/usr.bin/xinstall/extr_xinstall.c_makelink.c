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
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  lnk ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 scalar_t__ EXDEV ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int LN_ABSOLUTE ; 
 int LN_HARD ; 
 int LN_MIXED ; 
 int LN_RELATIVE ; 
 int MAXPATHLEN ; 
 scalar_t__ S_ISREG (int) ; 
 char* basename (char*) ; 
 char* digest_file (char const*) ; 
 char* dirname (char*) ; 
 int do_link (char const*,char const*,struct stat const*) ; 
 int /*<<< orphan*/  do_symlink (char const*,char const*,struct stat const*) ; 
 int dolink ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* fflags ; 
 int /*<<< orphan*/  free (char*) ; 
 char const* group ; 
 int /*<<< orphan*/  haveopt_f ; 
 int /*<<< orphan*/  haveopt_g ; 
 int /*<<< orphan*/  haveopt_m ; 
 int /*<<< orphan*/  haveopt_o ; 
 int /*<<< orphan*/  metadata_log (char const*,char*,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int mode ; 
 char const* owner ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 int strlcat (char*,char*,int) ; 

__attribute__((used)) static void
makelink(const char *from_name, const char *to_name,
    const struct stat *target_sb)
{
	char	src[MAXPATHLEN], dst[MAXPATHLEN], lnk[MAXPATHLEN];
	struct stat	to_sb;

	/* Try hard links first. */
	if (dolink & (LN_HARD|LN_MIXED)) {
		if (do_link(from_name, to_name, target_sb) == -1) {
			if ((dolink & LN_HARD) || errno != EXDEV)
				err(EX_OSERR, "link %s -> %s", from_name, to_name);
		} else {
			if (stat(to_name, &to_sb))
				err(EX_OSERR, "%s: stat", to_name);
			if (S_ISREG(to_sb.st_mode)) {
				/*
				 * XXX: hard links to anything other than
				 * plain files are not metalogged
				 */
				int omode;
				const char *oowner, *ogroup;
				char *offlags;
				char *dres;

				/*
				 * XXX: use underlying perms, unless
				 * overridden on command line.
				 */
				omode = mode;
				if (!haveopt_m)
					mode = (to_sb.st_mode & 0777);
				oowner = owner;
				if (!haveopt_o)
					owner = NULL;
				ogroup = group;
				if (!haveopt_g)
					group = NULL;
				offlags = fflags;
				if (!haveopt_f)
					fflags = NULL;
				dres = digest_file(from_name);
				metadata_log(to_name, "file", NULL, NULL,
				    dres, to_sb.st_size);
				free(dres);
				mode = omode;
				owner = oowner;
				group = ogroup;
				fflags = offlags;
			}
			return;
		}
	}

	/* Symbolic links. */
	if (dolink & LN_ABSOLUTE) {
		/* Convert source path to absolute. */
		if (realpath(from_name, src) == NULL)
			err(EX_OSERR, "%s: realpath", from_name);
		do_symlink(src, to_name, target_sb);
		/* XXX: src may point outside of destdir */
		metadata_log(to_name, "link", NULL, src, NULL, 0);
		return;
	}

	if (dolink & LN_RELATIVE) {
		char *to_name_copy, *cp, *d, *ld, *ls, *s;

		if (*from_name != '/') {
			/* this is already a relative link */
			do_symlink(from_name, to_name, target_sb);
			/* XXX: from_name may point outside of destdir. */
			metadata_log(to_name, "link", NULL, from_name, NULL, 0);
			return;
		}

		/* Resolve pathnames. */
		if (realpath(from_name, src) == NULL)
			err(EX_OSERR, "%s: realpath", from_name);

		/*
		 * The last component of to_name may be a symlink,
		 * so use realpath to resolve only the directory.
		 */
		to_name_copy = strdup(to_name);
		if (to_name_copy == NULL)
			err(EX_OSERR, "%s: strdup", to_name);
		cp = dirname(to_name_copy);
		if (realpath(cp, dst) == NULL)
			err(EX_OSERR, "%s: realpath", cp);
		/* .. and add the last component. */
		if (strcmp(dst, "/") != 0) {
			if (strlcat(dst, "/", sizeof(dst)) > sizeof(dst))
				errx(1, "resolved pathname too long");
		}
		strcpy(to_name_copy, to_name);
		cp = basename(to_name_copy);
		if (strlcat(dst, cp, sizeof(dst)) > sizeof(dst))
			errx(1, "resolved pathname too long");
		free(to_name_copy);

		/* Trim common path components. */
		ls = ld = NULL;
		for (s = src, d = dst; *s == *d; ls = s, ld = d, s++, d++)
			continue;
		/*
		 * If we didn't end after a directory separator, then we've
		 * falsely matched the last component.  For example, if one
		 * invoked install -lrs /lib/foo.so /libexec/ then the source
		 * would terminate just after the separator while the
		 * destination would terminate in the middle of 'libexec',
		 * leading to a full directory getting falsely eaten.
		 */
		if ((ls != NULL && *ls != '/') || (ld != NULL && *ld != '/'))
			s--, d--;
		while (*s != '/')
			s--, d--;

		/* Count the number of directories we need to backtrack. */
		for (++d, lnk[0] = '\0'; *d; d++)
			if (*d == '/')
				(void)strlcat(lnk, "../", sizeof(lnk));

		(void)strlcat(lnk, ++s, sizeof(lnk));

		do_symlink(lnk, to_name, target_sb);
		/* XXX: Link may point outside of destdir. */
		metadata_log(to_name, "link", NULL, lnk, NULL, 0);
		return;
	}

	/*
	 * If absolute or relative was not specified, try the names the
	 * user provided.
	 */
	do_symlink(from_name, to_name, target_sb);
	/* XXX: from_name may point outside of destdir. */
	metadata_log(to_name, "link", NULL, from_name, NULL, 0);
}