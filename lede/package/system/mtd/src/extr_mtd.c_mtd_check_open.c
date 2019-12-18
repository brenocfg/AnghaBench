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
struct mtd_info_user {int /*<<< orphan*/  type; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMGETINFO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  erasesize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mtd_info_user*) ; 
 int mtd_open (char const*,int) ; 
 int /*<<< orphan*/  mtdsize ; 
 int /*<<< orphan*/  mtdtype ; 
 int /*<<< orphan*/  stderr ; 

int mtd_check_open(const char *mtd)
{
	struct mtd_info_user mtdInfo;
	int fd;

	fd = mtd_open(mtd, false);
	if(fd < 0) {
		fprintf(stderr, "Could not open mtd device: %s\n", mtd);
		return -1;
	}

	if(ioctl(fd, MEMGETINFO, &mtdInfo)) {
		fprintf(stderr, "Could not get MTD device info from %s\n", mtd);
		close(fd);
		return -1;
	}
	mtdsize = mtdInfo.size;
	erasesize = mtdInfo.erasesize;
	mtdtype = mtdInfo.type;

	return fd;
}