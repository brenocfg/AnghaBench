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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  fn ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char const*,...) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int errno ; 
 int /*<<< orphan*/  fetch_info (char*) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int
fetch_netrc_open(void)
{
	struct passwd *pwd;
	char fn[PATH_MAX];
	const char *p;
	int fd, serrno;

	if ((p = getenv("NETRC")) != NULL) {
		DEBUGF("NETRC=%s\n", p);
		if (snprintf(fn, sizeof(fn), "%s", p) >= (int)sizeof(fn)) {
			fetch_info("$NETRC specifies a file name "
			    "longer than PATH_MAX");
			return (-1);
		}
	} else {
		if ((p = getenv("HOME")) == NULL) {
			if ((pwd = getpwuid(getuid())) == NULL ||
			    (p = pwd->pw_dir) == NULL)
				return (-1);
		}
		if (snprintf(fn, sizeof(fn), "%s/.netrc", p) >= (int)sizeof(fn))
			return (-1);
	}

	if ((fd = open(fn, O_RDONLY)) < 0) {
		serrno = errno;
		DEBUGF("%s: %s\n", fn, strerror(serrno));
		errno = serrno;
	}
	return (fd);
}