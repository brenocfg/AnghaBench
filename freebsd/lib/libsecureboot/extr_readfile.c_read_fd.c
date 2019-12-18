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

/* Variables and functions */
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 
 int read (int,unsigned char*,int) ; 

unsigned char *
read_fd(int fd, size_t len)
{
	int m, n, x;
	unsigned char *buf;

	buf = malloc(len + 1);
	for (x = 0, m = len; m > 0; ) {
		n = read(fd, &buf[x], m);
		if (n < 0)
			break;
		if (n > 0) {
			m -= n;
			x += n;
		}
	}
	if (m == 0) {
		buf[len] = '\0';
		return (buf);
	}
	free(buf);
	return (NULL);
}