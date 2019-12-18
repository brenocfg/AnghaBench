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
typedef  int ufs2_daddr_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGDELETE ; 
 int dev_bsize ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 

void
blerase(int fd, ufs2_daddr_t blk, long size)
{
	off_t ioarg[2];

	if (fd < 0)
		return;
	ioarg[0] = blk * dev_bsize;
	ioarg[1] = size;
	ioctl(fd, DIOCGDELETE, ioarg);
	/* we don't really care if we succeed or not */
	return;
}