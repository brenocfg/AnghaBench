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
typedef  int u_long ;
struct sshkey {int dummy; } ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __progname ; 
 int /*<<< orphan*/  ask_filename (struct passwd*,char*) ; 
 int /*<<< orphan*/  debug (char*,char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fingerprint_one_key (struct sshkey*,char*) ; 
 int /*<<< orphan*/  fingerprint_private (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_identity ; 
 char* identity_file ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strspn (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int strtol (char*,char**,int) ; 
 struct sshkey* try_read_key (char**) ; 

__attribute__((used)) static void
do_fingerprint(struct passwd *pw)
{
	FILE *f;
	struct sshkey *public = NULL;
	char *comment = NULL, *cp, *ep, *line = NULL;
	size_t linesize = 0;
	int i, invalid = 1;
	const char *path;
	u_long lnum = 0;

	if (!have_identity)
		ask_filename(pw, "Enter file in which the key is");
	path = identity_file;

	if (strcmp(identity_file, "-") == 0) {
		f = stdin;
		path = "(stdin)";
	} else if ((f = fopen(path, "r")) == NULL)
		fatal("%s: %s: %s", __progname, path, strerror(errno));

	while (getline(&line, &linesize, f) != -1) {
		lnum++;
		cp = line;
		cp[strcspn(cp, "\n")] = '\0';
		/* Trim leading space and comments */
		cp = line + strspn(line, " \t");
		if (*cp == '#' || *cp == '\0')
			continue;

		/*
		 * Input may be plain keys, private keys, authorized_keys
		 * or known_hosts.
		 */

		/*
		 * Try private keys first. Assume a key is private if
		 * "SSH PRIVATE KEY" appears on the first line and we're
		 * not reading from stdin (XXX support private keys on stdin).
		 */
		if (lnum == 1 && strcmp(identity_file, "-") != 0 &&
		    strstr(cp, "PRIVATE KEY") != NULL) {
			free(line);
			fclose(f);
			fingerprint_private(path);
			exit(0);
		}

		/*
		 * If it's not a private key, then this must be prepared to
		 * accept a public key prefixed with a hostname or options.
		 * Try a bare key first, otherwise skip the leading stuff.
		 */
		if ((public = try_read_key(&cp)) == NULL) {
			i = strtol(cp, &ep, 10);
			if (i == 0 || ep == NULL ||
			    (*ep != ' ' && *ep != '\t')) {
				int quoted = 0;

				comment = cp;
				for (; *cp && (quoted || (*cp != ' ' &&
				    *cp != '\t')); cp++) {
					if (*cp == '\\' && cp[1] == '"')
						cp++;	/* Skip both */
					else if (*cp == '"')
						quoted = !quoted;
				}
				if (!*cp)
					continue;
				*cp++ = '\0';
			}
		}
		/* Retry after parsing leading hostname/key options */
		if (public == NULL && (public = try_read_key(&cp)) == NULL) {
			debug("%s:%lu: not a public key", path, lnum);
			continue;
		}

		/* Find trailing comment, if any */
		for (; *cp == ' ' || *cp == '\t'; cp++)
			;
		if (*cp != '\0' && *cp != '#')
			comment = cp;

		fingerprint_one_key(public, comment);
		sshkey_free(public);
		invalid = 0; /* One good key in the file is sufficient */
	}
	fclose(f);
	free(line);

	if (invalid)
		fatal("%s is not a public key file.", path);
	exit(0);
}