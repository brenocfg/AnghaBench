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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  g_gate_xlog (char*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

unsigned
g_gate_sectorsize(int fd)
{
	unsigned secsize;
	struct stat sb;

	if (fstat(fd, &sb) == -1)
		g_gate_xlog("fstat(): %s.", strerror(errno));
	if (S_ISCHR(sb.st_mode)) {
		if (ioctl(fd, DIOCGSECTORSIZE, &secsize) == -1) {
			g_gate_xlog("Can't get sector size: %s.",
			    strerror(errno));
		}
	} else if (S_ISREG(sb.st_mode)) {
		secsize = 512;
	} else {
		g_gate_xlog("Unsupported file system object.");
	}
	return (secsize);
}