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
 scalar_t__ EINTR ; 
 int _write (int,char const*,size_t) ; 
 scalar_t__ errno ; 

__attribute__((used)) static bool
we_write_fully(int fd, const char *buffer, size_t len)
{
	size_t done;
	ssize_t nwritten;

	done = 0;
	do {
		nwritten = _write(fd, buffer + done, len - done);
		if (nwritten == -1 && errno == EINTR)
			continue;
		if (nwritten <= 0)
			return (false);
		done += nwritten;
	} while (done != len);
	return (true);
}