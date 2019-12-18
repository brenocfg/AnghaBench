#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
typedef  scalar_t__ regoff_t ;
struct TYPE_3__ {scalar_t__ rm_eo; scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  char* ccharp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  LC_ALL ; 
 char* LOCATECMD ; 
 char* MANWHEREISALLCMD ; 
 char* MANWHEREISCMD ; 
 char* MANWHEREISMATCH ; 
 int NO_BIN_FOUND ; 
 int NO_MAN_FOUND ; 
 int NO_SRC_FOUND ; 
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  abort () ; 
 char** bindirs ; 
 int /*<<< orphan*/  colonify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defaults () ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/ * mandirs ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ opt_a ; 
 scalar_t__ opt_b ; 
 scalar_t__ opt_m ; 
 int /*<<< orphan*/  opt_q ; 
 scalar_t__ opt_s ; 
 scalar_t__ opt_u ; 
 scalar_t__ opt_x ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char** query ; 
 char* realloc (char*,size_t) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scanopts (int,char**) ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 char** sourcedirs ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

int
main(int argc, char **argv)
{
	int unusual, i, printed;
	char *bin, buf[BUFSIZ], *cp, *cp2, *man, *name, *src;
	ccharp *dp;
	size_t nlen, olen, s;
	struct stat sb;
	regex_t re, re2;
	regmatch_t matches[2];
	regoff_t rlen;
	FILE *p;

	setlocale(LC_ALL, "");

	scanopts(argc, argv);
	defaults();

	if (mandirs == NULL)
		opt_m = 0;
	if (bindirs == NULL)
		opt_b = 0;
	if (sourcedirs == NULL)
		opt_s = 0;
	if (opt_m + opt_b + opt_s == 0)
		errx(EX_DATAERR, "no directories to search");

	if (opt_m) {
		setenv("MANPATH", colonify(mandirs), 1);
		if ((i = regcomp(&re, MANWHEREISMATCH, REG_EXTENDED)) != 0) {
			regerror(i, &re, buf, BUFSIZ - 1);
			errx(EX_UNAVAILABLE, "regcomp(%s) failed: %s",
			     MANWHEREISMATCH, buf);
		}
	}

	for (; (name = *query) != NULL; query++) {
		/* strip leading path name component */
		if ((cp = strrchr(name, '/')) != NULL)
			name = cp + 1;
		/* strip SCCS or RCS suffix/prefix */
		if (strlen(name) > 2 && strncmp(name, "s.", 2) == 0)
			name += 2;
		if ((s = strlen(name)) > 2 && strcmp(name + s - 2, ",v") == 0)
			name[s - 2] = '\0';
		/* compression suffix */
		s = strlen(name);
		if (s > 2 &&
		    (strcmp(name + s - 2, ".z") == 0 ||
		     strcmp(name + s - 2, ".Z") == 0))
			name[s - 2] = '\0';
		else if (s > 3 &&
			 strcmp(name + s - 3, ".gz") == 0)
			name[s - 3] = '\0';
		else if (s > 4 &&
			 strcmp(name + s - 4, ".bz2") == 0)
			name[s - 4] = '\0';

		unusual = 0;
		bin = man = src = NULL;
		s = strlen(name);

		if (opt_b) {
			/*
			 * Binaries have to match exactly, and must be regular
			 * executable files.
			 */
			unusual = unusual | NO_BIN_FOUND;
			for (dp = bindirs; *dp != NULL; dp++) {
				cp = malloc(strlen(*dp) + 1 + s + 1);
				if (cp == NULL)
					abort();
				strcpy(cp, *dp);
				strcat(cp, "/");
				strcat(cp, name);
				if (stat(cp, &sb) == 0 &&
				    (sb.st_mode & S_IFMT) == S_IFREG &&
				    (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
				    != 0) {
					unusual = unusual & ~NO_BIN_FOUND;
					if (bin == NULL) {
						bin = strdup(cp);
					} else {
						olen = strlen(bin);
						nlen = strlen(cp);
						bin = realloc(bin, 
							      olen + nlen + 2);
						if (bin == NULL)
							abort();
						strcat(bin, " ");
						strcat(bin, cp);
					}
					if (!opt_a) {
						free(cp);
						break;
					}
				}
				free(cp);
			}
		}

		if (opt_m) {
			/*
			 * Ask the man command to perform the search for us.
			 */
			unusual = unusual | NO_MAN_FOUND;
			if (opt_a)
				cp = malloc(sizeof MANWHEREISALLCMD - 2 + s);
			else
				cp = malloc(sizeof MANWHEREISCMD - 2 + s);

			if (cp == NULL)
				abort();

			if (opt_a)
				sprintf(cp, MANWHEREISALLCMD, name);
			else
				sprintf(cp, MANWHEREISCMD, name);

			if ((p = popen(cp, "r")) != NULL) {
			    
				while (fgets(buf, BUFSIZ - 1, p) != NULL) {
					unusual = unusual & ~NO_MAN_FOUND;
				
					if ((cp2 = strchr(buf, '\n')) != NULL)
						*cp2 = '\0';
					if (regexec(&re, buf, 2, 
						    matches, 0) == 0 &&
					    (rlen = matches[1].rm_eo - 
					     matches[1].rm_so) > 0) {
						/*
						 * man -w found formatted
						 * page, need to pick up
						 * source page name.
						 */
						cp2 = malloc(rlen + 1);
						if (cp2 == NULL)
							abort();
						memcpy(cp2, 
						       buf + matches[1].rm_so,
						       rlen);
						cp2[rlen] = '\0';
					} else {
						/*
						 * man -w found plain source
						 * page, use it.
						 */
						cp2 = strdup(buf);
						if (cp2 == NULL)
							abort();
					}

					if (man == NULL) {
						man = strdup(cp2);
					} else {
						olen = strlen(man);
						nlen = strlen(cp2);
						man = realloc(man, 
							      olen + nlen + 2);
						if (man == NULL)
							abort();
						strcat(man, " ");
						strcat(man, cp2);
					}

					free(cp2);
					
					if (!opt_a)
						break;
				}
				pclose(p);
				free(cp);
			}
		}

		if (opt_s) {
			/*
			 * Sources match if a subdir with the exact
			 * name is found.
			 */
			unusual = unusual | NO_SRC_FOUND;
			for (dp = sourcedirs; *dp != NULL; dp++) {
				cp = malloc(strlen(*dp) + 1 + s + 1);
				if (cp == NULL)
					abort();
				strcpy(cp, *dp);
				strcat(cp, "/");
				strcat(cp, name);
				if (stat(cp, &sb) == 0 &&
				    (sb.st_mode & S_IFMT) == S_IFDIR) {
					unusual = unusual & ~NO_SRC_FOUND;
					if (src == NULL) {
						src = strdup(cp);
					} else {
						olen = strlen(src);
						nlen = strlen(cp);
						src = realloc(src, 
							      olen + nlen + 2);
						if (src == NULL)
							abort();
						strcat(src, " ");
						strcat(src, cp);
					}
					if (!opt_a) {
						free(cp);
						break;
					}
				}
				free(cp);
			}
			/*
			 * If still not found, ask locate to search it
			 * for us.  This will find sources for things
			 * like lpr that are well hidden in the
			 * /usr/src tree, but takes a lot longer.
			 * Thus, option -x (`expensive') prevents this
			 * search.
			 *
			 * Do only match locate output that starts
			 * with one of our source directories, and at
			 * least one further level of subdirectories.
			 */
			if (opt_x || (src && !opt_a))
				goto done_sources;

			cp = malloc(sizeof LOCATECMD - 2 + s);
			if (cp == NULL)
				abort();
			sprintf(cp, LOCATECMD, name);
			if ((p = popen(cp, "r")) == NULL)
				goto done_sources;
			while ((src == NULL || opt_a) &&
			       (fgets(buf, BUFSIZ - 1, p)) != NULL) {
				if ((cp2 = strchr(buf, '\n')) != NULL)
					*cp2 = '\0';
				for (dp = sourcedirs;
				     (src == NULL || opt_a) && *dp != NULL;
				     dp++) {
					cp2 = malloc(strlen(*dp) + 9);
					if (cp2 == NULL)
						abort();
					strcpy(cp2, "^");
					strcat(cp2, *dp);
					strcat(cp2, "/[^/]+/");
					if ((i = regcomp(&re2, cp2,
							 REG_EXTENDED|REG_NOSUB))
					    != 0) {
						regerror(i, &re, buf,
							 BUFSIZ - 1);
						errx(EX_UNAVAILABLE,
						     "regcomp(%s) failed: %s",
						     cp2, buf);
					}
					free(cp2);
					if (regexec(&re2, buf, 0,
						    (regmatch_t *)NULL, 0)
					    == 0) {
						unusual = unusual & 
						          ~NO_SRC_FOUND;
						if (src == NULL) {
							src = strdup(buf);
						} else {
							olen = strlen(src);
							nlen = strlen(buf);
							src = realloc(src, 
								      olen + 
								      nlen + 2);
							if (src == NULL)
								abort();
							strcat(src, " ");
							strcat(src, buf);
						}
					}
					regfree(&re2);
				}
			}
			pclose(p);
			free(cp);
		}
	  done_sources:

		if (opt_u && !unusual)
			continue;

		printed = 0;
		if (!opt_q) {
			printf("%s:", name);
			printed++;
		}
		if (bin) {
			if (printed++)
				putchar(' ');
			fputs(bin, stdout);
		}
		if (man) {
			if (printed++)
				putchar(' ');
			fputs(man, stdout);
		}
		if (src) {
			if (printed++)
				putchar(' ');
			fputs(src, stdout);
		}
		if (printed)
			putchar('\n');
	}

	if (opt_m)
		regfree(&re);

	return (0);
}