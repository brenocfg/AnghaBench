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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  g_gate_xlog (char*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

off_t
g_gate_mediasize(int fd)
{
	off_t mediasize;
	struct stat sb;

	if (fstat(fd, &sb) == -1)
		g_gate_xlog("fstat(): %s.", strerror(errno));
	if (S_ISCHR(sb.st_mode)) {
		if (ioctl(fd, DIOCGMEDIASIZE, &mediasize) == -1) {
			g_gate_xlog("Can't get media size: %s.",
			    strerror(errno));
		}
	} else if (S_ISREG(sb.st_mode)) {
		mediasize = sb.st_size;
	} else {
		g_gate_xlog("Unsupported file system object.");
	}
	return (mediasize);
}