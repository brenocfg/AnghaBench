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
 int /*<<< orphan*/  BUFSIZ ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int recv (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
copybytes(int sd, int fd, off_t copylen, char * resbuf, int * resbuflen,
    int * resbufpos)
{
	ssize_t len;

	while (copylen) {
		/* Write data from resbuf to fd */
		len = *resbuflen - *resbufpos;
		if (copylen < len)
			len = copylen;
		if (len > 0) {
			if (fd != -1)
				len = write(fd, resbuf + *resbufpos, len);
			if (len == -1)
				err(1, "write");
			*resbufpos += len;
			copylen -= len;
			continue;
		}

		/* Read more data into buffer */
		len = recv(sd, resbuf, BUFSIZ, 0);
		if (len == -1) {
			if (errno == EINTR)
				continue;
			return -1;
		} else if (len == 0) {
			return -2;
		} else {
			*resbuflen = len;
			*resbufpos = 0;
		}
	}

	return 0;
}