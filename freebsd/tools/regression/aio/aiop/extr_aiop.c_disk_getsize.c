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
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static size_t
disk_getsize(int fd)
{
	off_t mediasize;	

	if (ioctl(fd, DIOCGMEDIASIZE, &mediasize) < 0)
		err(1, "ioctl(DIOCGMEDIASIZE)");
	return (mediasize);
}