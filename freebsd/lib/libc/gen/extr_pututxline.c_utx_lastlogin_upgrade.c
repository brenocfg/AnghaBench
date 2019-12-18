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
struct stat {int st_size; } ;
struct futx {int dummy; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _PATH_UTX_LASTLOGIN ; 
 int /*<<< orphan*/  _close (int) ; 
 int _fstat (int,struct stat*) ; 
 int _open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ftruncate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
utx_lastlogin_upgrade(void)
{
	struct stat sb;
	int fd;

	fd = _open(_PATH_UTX_LASTLOGIN, O_RDWR|O_CLOEXEC, 0644);
	if (fd < 0)
		return;

	/*
	 * Truncate broken lastlogin files.  In the future we should
	 * check for older versions of the file format here and try to
	 * upgrade it.
	 */
	if (_fstat(fd, &sb) != -1 && sb.st_size % sizeof(struct futx) != 0)
		ftruncate(fd, 0);
	_close(fd);
}