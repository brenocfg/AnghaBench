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
typedef  int /*<<< orphan*/  binpath ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int O_VERIFY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  _rtld_error (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  rtld_die () ; 
 int /*<<< orphan*/  rtld_strerror (scalar_t__) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strdup (char*) ; 
 int strlcat (char*,char const*,int) ; 
 int strlcpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
open_binary_fd(const char *argv0, bool search_in_path)
{
	char *pathenv, *pe, binpath[PATH_MAX];
	int fd;

	if (search_in_path && strchr(argv0, '/') == NULL) {
		pathenv = getenv("PATH");
		if (pathenv == NULL) {
			_rtld_error("-p and no PATH environment variable");
			rtld_die();
		}
		pathenv = strdup(pathenv);
		if (pathenv == NULL) {
			_rtld_error("Cannot allocate memory");
			rtld_die();
		}
		fd = -1;
		errno = ENOENT;
		while ((pe = strsep(&pathenv, ":")) != NULL) {
			if (strlcpy(binpath, pe, sizeof(binpath)) >=
			    sizeof(binpath))
				continue;
			if (binpath[0] != '\0' &&
			    strlcat(binpath, "/", sizeof(binpath)) >=
			    sizeof(binpath))
				continue;
			if (strlcat(binpath, argv0, sizeof(binpath)) >=
			    sizeof(binpath))
				continue;
			fd = open(binpath, O_RDONLY | O_CLOEXEC | O_VERIFY);
			if (fd != -1 || errno != ENOENT)
				break;
		}
		free(pathenv);
	} else {
		fd = open(argv0, O_RDONLY | O_CLOEXEC | O_VERIFY);
	}

	if (fd == -1) {
		_rtld_error("Cannot open %s: %s", argv0, rtld_strerror(errno));
		rtld_die();
	}
	return (fd);
}