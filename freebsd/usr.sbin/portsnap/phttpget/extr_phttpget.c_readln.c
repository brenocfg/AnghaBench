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
 int BUFSIZ ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strnstr (char*,char*,int) ; 

__attribute__((used)) static int
readln(int sd, char * resbuf, int * resbuflen, int * resbufpos)
{
	ssize_t len;

	while (strnstr(resbuf + *resbufpos, "\r\n",
	    *resbuflen - *resbufpos) == NULL) {
		/* Move buffered data to the start of the buffer */
		if (*resbufpos != 0) {
			memmove(resbuf, resbuf + *resbufpos,
			    *resbuflen - *resbufpos);
			*resbuflen -= *resbufpos;
			*resbufpos = 0;
		}

		/* If the buffer is full, complain */
		if (*resbuflen == BUFSIZ)
			return -1;

		/* Read more data into the buffer */
		len = recv(sd, resbuf + *resbuflen, BUFSIZ - *resbuflen, 0);
		if ((len == 0) ||
		    ((len == -1) && (errno != EINTR)))
			return -1;

		if (len != -1)
			*resbuflen += len;
	}

	return 0;
}