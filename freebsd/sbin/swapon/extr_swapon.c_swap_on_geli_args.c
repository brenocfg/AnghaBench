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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ Eflag ; 
 scalar_t__ INT_MAX ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int getpagesize () ; 
 int snprintf (char*,size_t,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static char *
swap_on_geli_args(const char *mntops)
{
	const char *aalgo, *ealgo, *keylen_str, *sectorsize_str;
	const char *aflag, *eflag, *lflag, *Tflag, *sflag;
	char *p, *args, *token, *string, *ops;
	int pagesize;
	size_t pagesize_len;
	u_long ul;

	/* Use built-in defaults for geli(8). */
	aalgo = ealgo = keylen_str = "";
	aflag = eflag = lflag = Tflag = "";

	/* We will always specify sectorsize. */
	sflag = " -s ";
	sectorsize_str = NULL;

	if (mntops != NULL) {
		string = ops = strdup(mntops);

		while ((token = strsep(&string, ",")) != NULL) {
			if ((p = strstr(token, "aalgo=")) == token) {
				aalgo = p + sizeof("aalgo=") - 1;
				aflag = " -a ";
			} else if ((p = strstr(token, "ealgo=")) == token) {
				ealgo = p + sizeof("ealgo=") - 1;
				eflag = " -e ";
			} else if ((p = strstr(token, "keylen=")) == token) {
				keylen_str = p + sizeof("keylen=") - 1;
				errno = 0;
				ul = strtoul(keylen_str, &p, 10);
				if (errno == 0) {
					if (*p != '\0' || ul > INT_MAX)
						errno = EINVAL;
				}
				if (errno) {
					warn("Invalid keylen: %s", keylen_str);
					free(ops);
					return (NULL);
				}
				lflag = " -l ";
			} else if ((p = strstr(token, "sectorsize=")) == token) {
				sectorsize_str = p + sizeof("sectorsize=") - 1;
				errno = 0;
				ul = strtoul(sectorsize_str, &p, 10);
				if (errno == 0) {
					if (*p != '\0' || ul > INT_MAX)
						errno = EINVAL;
				}
				if (errno) {
					warn("Invalid sectorsize: %s",
					    sectorsize_str);
					free(ops);
					return (NULL);
				}
			} else if (strcmp(token, "notrim") == 0) {
				if (Eflag) {
					warn("Options \"notrim\" and "
					    "\"trimonce\" conflict");
					free(ops);
					return (NULL);
				}
				Tflag = " -T ";
			} else if (strcmp(token, "late") == 0) {
				/* ignore known option */
			} else if (strcmp(token, "noauto") == 0) {
				/* ignore known option */
			} else if (strcmp(token, "sw") == 0) {
				/* ignore known option */
			} else if (strcmp(token, "trimonce") == 0) {
				/* ignore known option */
			} else {
				warnx("Invalid option: %s", token);
				free(ops);
				return (NULL);
			}
		}
	} else
		ops = NULL;

	/*
	 * If we do not have a sector size at this point, fill in
	 * pagesize as sector size.
	 */
	if (sectorsize_str == NULL) {
		/* Use pagesize as default sectorsize. */
		pagesize = getpagesize();
		pagesize_len = snprintf(NULL, 0, "%d", pagesize) + 1;
		p = alloca(pagesize_len);
		snprintf(p, pagesize_len, "%d", pagesize);
		sectorsize_str = p;
	}

	(void)asprintf(&args, "%s%s%s%s%s%s%s%s%s -d",
	    aflag, aalgo, eflag, ealgo, lflag, keylen_str, Tflag,
	    sflag, sectorsize_str);

	free(ops);
	return (args);
}