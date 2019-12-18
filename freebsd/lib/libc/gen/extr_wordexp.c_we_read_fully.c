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
 int _read (int,char*,size_t) ; 
 scalar_t__ errno ; 

__attribute__((used)) static size_t
we_read_fully(int fd, char *buffer, size_t len)
{
	size_t done;
	ssize_t nread;

	done = 0;
	do {
		nread = _read(fd, buffer + done, len - done);
		if (nread == -1 && errno == EINTR)
			continue;
		if (nread <= 0)
			break;
		done += nread;
	} while (done != len);
	return done;
}