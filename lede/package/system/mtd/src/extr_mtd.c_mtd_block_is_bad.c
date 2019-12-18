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
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEMGETBADBLOCK ; 
 scalar_t__ MTD_NANDFLASH ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mtdtype ; 
 int /*<<< orphan*/  stderr ; 

int mtd_block_is_bad(int fd, int offset)
{
	int r = 0;
	loff_t o = offset;

	if (mtdtype == MTD_NANDFLASH)
	{
		r = ioctl(fd, MEMGETBADBLOCK, &o);
		if (r < 0)
		{
			fprintf(stderr, "Failed to get erase block status\n");
			exit(1);
		}
	}
	return r;
}