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

/* Variables and functions */
 scalar_t__ ENOENT ; 
 long NAME_MAX ; 
 long PATH_MAX ; 
 scalar_t__ Pflag ; 
 int /*<<< orphan*/  _PC_NAME_MAX ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 long _POSIX_NAME_MAX ; 
 long _POSIX_PATH_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 long pathconf (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pflag ; 
 int /*<<< orphan*/  portable (char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcspn (char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*,int,char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
check(const char *path)
{
	struct stat sb;
	long complen, namemax, pathmax, svnamemax;
	int last;
	char *end, *p, *pathd;

	if ((pathd = strdup(path)) == NULL)
		err(1, "strdup");

	p = pathd;

	if (Pflag && *p == '\0') {
		warnx("%s: empty pathname", path);
		goto bad;
	}
	if ((Pflag || pflag) && (*p == '-' || strstr(p, "/-") != NULL)) {
		warnx("%s: contains a component starting with '-'", path);
		goto bad;
	}

	if (!pflag) {
		errno = 0;
		namemax = pathconf(*p == '/' ? "/" : ".", _PC_NAME_MAX);
		if (namemax == -1 && errno != 0)
			namemax = NAME_MAX;
	} else
		namemax = _POSIX_NAME_MAX;

	for (;;) {
		p += strspn(p, "/");
		complen = (long)strcspn(p, "/");
		end = p + complen;
		last = *end == '\0';
		*end = '\0';

		if (namemax != -1 && complen > namemax) {
			warnx("%s: %s: component too long (limit %ld)", path,
			    p, namemax);
			goto bad;
		}

		if (!pflag && stat(pathd, &sb) == -1 && errno != ENOENT) {
			warn("%s: %.*s", path, (int)(strlen(pathd) -
			    complen - 1), pathd);
			goto bad;
		}

		if (pflag && !portable(p)) {
			warnx("%s: %s: component contains non-portable "
			    "character", path, p);
			goto bad;
		}

		if (last)
			break;

		if (!pflag) {
			errno = 0;
			svnamemax = namemax;
			namemax = pathconf(pathd, _PC_NAME_MAX);
			if (namemax == -1 && errno != 0)
				namemax = svnamemax;
		}

		*end = '/';
		p = end + 1;
	}

	if (!pflag) {
		errno = 0;
		pathmax = pathconf(path, _PC_PATH_MAX);
		if (pathmax == -1 && errno != 0)
			pathmax = PATH_MAX;
	} else
		pathmax = _POSIX_PATH_MAX;
	if (pathmax != -1 && strlen(path) >= (size_t)pathmax) {
		warnx("%s: path too long (limit %ld)", path, pathmax - 1);
		goto bad;
	}

	free(pathd);
	return (0);

bad:	free(pathd);
	return (1);
}