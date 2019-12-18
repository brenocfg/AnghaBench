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
typedef  int /*<<< orphan*/  u_char ;
struct evbuffer {size_t off; int totallen; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cb ) (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int EVBUFFER_MAX_READ ; 
 int /*<<< orphan*/  FIONREAD ; 
 int ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int evbuffer_expand (struct evbuffer*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ; 

int
evbuffer_read(struct evbuffer *buf, int fd, int howmuch)
{
	u_char *p;
	size_t oldoff = buf->off;
	int n = EVBUFFER_MAX_READ;
#ifdef WIN32
	DWORD dwBytesRead;
#endif

#ifdef FIONREAD
	if (ioctl(fd, FIONREAD, &n) == -1 || n == 0) {
		n = EVBUFFER_MAX_READ;
	} else if (n > EVBUFFER_MAX_READ && n > howmuch) {
		/*
		 * It's possible that a lot of data is available for
		 * reading.  We do not want to exhaust resources
		 * before the reader has a chance to do something
		 * about it.  If the reader does not tell us how much
		 * data we should read, we artifically limit it.
		 */
		if (n > buf->totallen << 2)
			n = buf->totallen << 2;
		if (n < EVBUFFER_MAX_READ)
			n = EVBUFFER_MAX_READ;
	}
#endif	
	if (howmuch < 0 || howmuch > n)
		howmuch = n;

	/* If we don't have FIONREAD, we might waste some space here */
	if (evbuffer_expand(buf, howmuch) == -1)
		return (-1);

	/* We can append new data at this point */
	p = buf->buffer + buf->off;

#ifndef WIN32
	n = read(fd, p, howmuch);
	if (n == -1)
		return (-1);
	if (n == 0)
		return (0);
#else
	n = ReadFile((HANDLE)fd, p, howmuch, &dwBytesRead, NULL);
	if (n == 0)
		return (-1);
	if (dwBytesRead == 0)
		return (0);
	n = dwBytesRead;
#endif

	buf->off += n;

	/* Tell someone about changes in this buffer */
	if (buf->off != oldoff && buf->cb != NULL)
		(*buf->cb)(buf, oldoff, buf->off, buf->cbarg);

	return (n);
}