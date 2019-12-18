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
 int AT_FDCWD ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int O_BINARY ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_EXEC ; 
 int O_PATH ; 
 int O_RDONLY ; 
 int O_SEARCH ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int const) ; 
 int openat (int,char const*,int const) ; 

__attribute__((used)) static int
la_opendirat(int fd, const char *path) {
	const int flags = O_CLOEXEC
#if defined(O_BINARY)
	    | O_BINARY
#endif
#if defined(O_DIRECTORY)
	    | O_DIRECTORY
#endif
#if defined(O_PATH)
	    | O_PATH
#elif defined(O_SEARCH)
	    | O_SEARCH
#elif defined(O_EXEC)
	    | O_EXEC
#else
	    | O_RDONLY
#endif
	    ;

#if !defined(HAVE_OPENAT)
	if (fd != AT_FDCWD) {
		errno = ENOTSUP;
		return (-1);
	} else
		return (open(path, flags));
#else
	return (openat(fd, path, flags));
#endif
}