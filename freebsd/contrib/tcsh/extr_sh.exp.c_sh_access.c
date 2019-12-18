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
struct stat {int st_mode; scalar_t__ st_uid; scalar_t__ st_gid; } ;
typedef  scalar_t__ GETGROUPS_T ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 long NGROUPS_MAX ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
#define  W_OK 129 
#define  X_OK 128 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ access (char*,int) ; 
 scalar_t__ egid ; 
 scalar_t__ euid ; 
 long getgroups (int,scalar_t__*) ; 
 char* short2str (int /*<<< orphan*/  const*) ; 
 int stat (char*,struct stat*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (scalar_t__*) ; 
 scalar_t__* xmalloc (long) ; 

__attribute__((used)) static int
sh_access(const Char *fname, int mode)
{
#if defined(POSIX) && !defined(USE_ACCESS)
    struct stat     statb;
#endif /* POSIX */
    char *name = short2str(fname);

    if (*name == '\0')
	return 1;

#if !defined(POSIX) || defined(USE_ACCESS)
    return access(name, mode);
#else /* POSIX */

    /*
     * POSIX 1003.2-d11.2 
     *	-r file		True if file exists and is readable. 
     *	-w file		True if file exists and is writable. 
     *			True shall indicate only that the write flag is on. 
     *			The file shall not be writable on a read-only file
     *			system even if this test indicates true.
     *	-x file		True if file exists and is executable. 
     *			True shall indicate only that the execute flag is on. 
     *			If file is a directory, true indicates that the file 
     *			can be searched.
     */
    if (mode != W_OK && mode != X_OK)
	return access(name, mode);

    if (stat(name, &statb) == -1) 
	return 1;

    if (access(name, mode) == 0) {
#ifdef S_ISDIR
	if (S_ISDIR(statb.st_mode) && mode == X_OK)
	    return 0;
#endif /* S_ISDIR */

	/* root needs permission for someone */
	switch (mode) {
	case W_OK:
	    mode = S_IWUSR | S_IWGRP | S_IWOTH;
	    break;
	case X_OK:
	    mode = S_IXUSR | S_IXGRP | S_IXOTH;
	    break;
	default:
	    abort();
	    break;
	}

    } 

    else if (euid == statb.st_uid)
	mode <<= 6;

    else if (egid == statb.st_gid)
	mode <<= 3;

# ifdef NGROUPS_MAX
    else {
	/* you can be in several groups */
	long	n;
	GETGROUPS_T *groups;

	/*
	 * Try these things to find a positive maximum groups value:
	 *   1) sysconf(_SC_NGROUPS_MAX)
	 *   2) NGROUPS_MAX
	 *   3) getgroups(0, unused)
	 * Then allocate and scan the groups array if one of these worked.
	 */
#  if defined (HAVE_SYSCONF) && defined (_SC_NGROUPS_MAX)
	if ((n = sysconf(_SC_NGROUPS_MAX)) == -1)
#  endif /* _SC_NGROUPS_MAX */
	    n = NGROUPS_MAX;
	if (n <= 0)
	    n = getgroups(0, (GETGROUPS_T *) NULL);

	if (n > 0) {
	    groups = xmalloc(n * sizeof(*groups));
	    n = getgroups((int) n, groups);
	    while (--n >= 0)
		if (groups[n] == statb.st_gid) {
		    mode <<= 3;
		    break;
		}
	    xfree(groups);
	}
    }
# endif /* NGROUPS_MAX */

    if (statb.st_mode & mode)
	return 0;
    else
	return 1;
#endif /* !POSIX */
}