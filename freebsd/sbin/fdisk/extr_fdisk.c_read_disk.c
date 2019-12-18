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
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int MAX_SEC_SIZE ; 
 int MIN_SEC_SIZE ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,void*,int) ; 
 int secsize ; 

__attribute__((used)) static ssize_t
read_disk(off_t sector, void *buf)
{

	lseek(fd, (sector * 512), 0);
	if (secsize == 0)
		for (secsize = MIN_SEC_SIZE; secsize <= MAX_SEC_SIZE;
		     secsize *= 2) {
			/* try the read */
			int size = read(fd, buf, secsize);
			if (size == secsize)
				/* it worked so return */
				return secsize;
		}
	else
		return read(fd, buf, secsize);

	/* we failed to read at any of the sizes */
	return -1;
}