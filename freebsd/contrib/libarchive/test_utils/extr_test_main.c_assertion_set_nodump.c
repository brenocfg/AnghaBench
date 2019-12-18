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
 int /*<<< orphan*/  EXT2_IOC_GETFLAGS ; 
 int /*<<< orphan*/  EXT2_IOC_SETFLAGS ; 
 int EXT2_NODUMP_FL ; 
 int /*<<< orphan*/  FS_IOC_GETFLAGS ; 
 int /*<<< orphan*/  FS_IOC_SETFLAGS ; 
 int FS_NODUMP_FL ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  UF_NODUMP ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int chflags (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int open (char const*,int) ; 

int
assertion_set_nodump(const char *file, int line, const char *pathname)
{
#if defined(HAVE_STRUCT_STAT_ST_FLAGS) && defined(UF_NODUMP)
	int r;

	assertion_count(file, line);
	r = chflags(pathname, UF_NODUMP);
	if (r < 0) {
		failure_start(file, line, "Can't set nodump %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
#elif (defined(FS_IOC_GETFLAGS) && defined(HAVE_WORKING_FS_IOC_GETFLAGS) && \
       defined(FS_NODUMP_FL)) || \
      (defined(EXT2_IOC_GETFLAGS) && defined(HAVE_WORKING_EXT2_IOC_GETFLAGS) \
	 && defined(EXT2_NODUMP_FL))
	int fd, r, flags;

	assertion_count(file, line);
	fd = open(pathname, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		failure_start(file, line, "Can't open %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	r = ioctl(fd,
#ifdef FS_IOC_GETFLAGS
	    FS_IOC_GETFLAGS,
#else
	    EXT2_IOC_GETFLAGS,
#endif
	    &flags);
	if (r < 0) {
		failure_start(file, line, "Can't get flags %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
#ifdef FS_NODUMP_FL
	flags |= FS_NODUMP_FL;
#else
	flags |= EXT2_NODUMP_FL;
#endif

	 r = ioctl(fd,
#ifdef FS_IOC_SETFLAGS
	    FS_IOC_SETFLAGS,
#else
	    EXT2_IOC_SETFLAGS,
#endif
	    &flags);
	if (r < 0) {
		failure_start(file, line, "Can't set nodump %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	close(fd);
#else
	(void)pathname; /* UNUSED */
	assertion_count(file, line);
#endif
	return (1);
}