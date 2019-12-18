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
struct stat {scalar_t__ st_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_IOC_GETFLAGS ; 
 int /*<<< orphan*/  FS_IOC_GETFLAGS ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int open (char const*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int
assertion_compare_fflags(const char *file, int line, const char *patha,
    const char *pathb, int nomatch)
{
#if defined(HAVE_STRUCT_STAT_ST_FLAGS) && defined(UF_NODUMP)
	struct stat sa, sb;

	assertion_count(file, line);

	if (stat(patha, &sa) < 0)
		return (0);
	if (stat(pathb, &sb) < 0)
		return (0);
	if (!nomatch && sa.st_flags != sb.st_flags) {
		failure_start(file, line, "File flags should be identical: "
		    "%s=%#010x %s=%#010x", patha, sa.st_flags, pathb,
		    sb.st_flags);
		failure_finish(NULL);
		return (0);
	}
	if (nomatch && sa.st_flags == sb.st_flags) {
		failure_start(file, line, "File flags should be different: "
		    "%s=%#010x %s=%#010x", patha, sa.st_flags, pathb,
		    sb.st_flags);
		failure_finish(NULL);
		return (0);
	}
#elif (defined(FS_IOC_GETFLAGS) && defined(HAVE_WORKING_FS_IOC_GETFLAGS) && \
       defined(FS_NODUMP_FL)) || \
      (defined(EXT2_IOC_GETFLAGS) && defined(HAVE_WORKING_EXT2_IOC_GETFLAGS) \
         && defined(EXT2_NODUMP_FL))
	int fd, r, flagsa, flagsb;

	assertion_count(file, line);
	fd = open(patha, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		failure_start(file, line, "Can't open %s\n", patha);
		failure_finish(NULL);
		return (0);
	}
	r = ioctl(fd,
#ifdef FS_IOC_GETFLAGS
	    FS_IOC_GETFLAGS,
#else
	    EXT2_IOC_GETFLAGS,
#endif
	    &flagsa);
	close(fd);
	if (r < 0) {
		failure_start(file, line, "Can't get flags %s\n", patha);
		failure_finish(NULL);
		return (0);
	}
	fd = open(pathb, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		failure_start(file, line, "Can't open %s\n", pathb);
		failure_finish(NULL);
		return (0);
	}
	r = ioctl(fd,
#ifdef FS_IOC_GETFLAGS
	    FS_IOC_GETFLAGS,
#else
	    EXT2_IOC_GETFLAGS,
#endif
	    &flagsb);
	close(fd);
	if (r < 0) {
		failure_start(file, line, "Can't get flags %s\n", pathb);
		failure_finish(NULL);
		return (0);
	}
	if (!nomatch && flagsa != flagsb) {
		failure_start(file, line, "File flags should be identical: "
		    "%s=%#010x %s=%#010x", patha, flagsa, pathb, flagsb);
		failure_finish(NULL);
		return (0);
	}
	if (nomatch && flagsa == flagsb) {
		failure_start(file, line, "File flags should be different: "
		    "%s=%#010x %s=%#010x", patha, flagsa, pathb, flagsb);
		failure_finish(NULL);
		return (0);
	}
#else
	(void)patha; /* UNUSED */
	(void)pathb; /* UNUSED */
	(void)nomatch; /* UNUSED */
	assertion_count(file, line);
#endif
	return (1);
}