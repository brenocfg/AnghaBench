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
 int /*<<< orphan*/  FS_IOC_GETFLAGS ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  chflags (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
clear_fflags(const char *pathname)
{
#if defined(HAVE_STRUCT_STAT_ST_FLAGS)
	chflags(pathname, 0);
#elif (defined(FS_IOC_GETFLAGS) && defined(HAVE_WORKING_FS_IOC_GETFLAGS)) || \
      (defined(EXT2_IOC_GETFLAGS) && defined(HAVE_WORKING_EXT2_IOC_GETFLAGS))
	int fd;

	fd = open(pathname, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
		return;
	ioctl(fd,
#ifdef FS_IOC_GETFLAGS
	    FS_IOC_GETFLAGS,
#else
	    EXT2_IOC_GETFLAGS,
#endif
	    0);
#else
	(void)pathname; /* UNUSED */
#endif
	return;
}