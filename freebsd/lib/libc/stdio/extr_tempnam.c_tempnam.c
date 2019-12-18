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

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* P_tmpdir ; 
 char* _PATH_TMP ; 
 char* _mktemp (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ issetugid () ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int strlen (char*) ; 

char *
tempnam(const char *dir, const char *pfx)
{
	int sverrno;
	char *f, *name;

	if (!(name = malloc(MAXPATHLEN)))
		return(NULL);

	if (!pfx)
		pfx = "tmp.";

	if (issetugid() == 0 && (f = getenv("TMPDIR"))) {
		(void)snprintf(name, MAXPATHLEN, "%s%s%sXXXXXX", f,
		    *(f + strlen(f) - 1) == '/'? "": "/", pfx);
		if ((f = _mktemp(name)))
			return(f);
	}

	if ((f = (char *)dir)) {
		(void)snprintf(name, MAXPATHLEN, "%s%s%sXXXXXX", f,
		    *(f + strlen(f) - 1) == '/'? "": "/", pfx);
		if ((f = _mktemp(name)))
			return(f);
	}

	f = P_tmpdir;
	(void)snprintf(name, MAXPATHLEN, "%s%sXXXXXX", f, pfx);
	if ((f = _mktemp(name)))
		return(f);

	f = _PATH_TMP;
	(void)snprintf(name, MAXPATHLEN, "%s%sXXXXXX", f, pfx);
	if ((f = _mktemp(name)))
		return(f);

	sverrno = errno;
	free(name);
	errno = sverrno;
	return(NULL);
}