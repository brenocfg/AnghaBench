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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EIO ; 
 int pwrite (int,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
use_pwrite(void *devfd, off_t loc, void *buf, int size)
{
	int fd;

	fd = *(int *)devfd;
	if (pwrite(fd, buf, size, loc) != size)
		return (EIO);
	return (0);
}