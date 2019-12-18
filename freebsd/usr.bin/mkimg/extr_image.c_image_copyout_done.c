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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int errno ; 
 int ftruncate (int,int) ; 
 int lseek (int,long,int /*<<< orphan*/ ) ; 

int
image_copyout_done(int fd)
{
	off_t ofs;
	int error;

	ofs = lseek(fd, 0L, SEEK_CUR);
	if (ofs == -1)
		return (0);
	error = (ftruncate(fd, ofs) == -1) ? errno : 0;
	return (error);
}