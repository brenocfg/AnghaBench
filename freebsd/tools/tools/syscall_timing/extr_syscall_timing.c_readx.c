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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int read (int,char*,size_t) ; 

__attribute__((used)) static void
readx(int fd, char *buf, size_t size)
{
	ssize_t ret;

	do {
		ret = read(fd, buf, size);
		if (ret == -1)
			err(1, "read");
		assert((size_t)ret <= size);
		size -= ret;
		buf += ret;
	} while (size > 0);
}