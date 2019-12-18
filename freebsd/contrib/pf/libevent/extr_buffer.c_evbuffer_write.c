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
struct evbuffer {int /*<<< orphan*/  off; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int) ; 
 int write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
evbuffer_write(struct evbuffer *buffer, int fd)
{
	int n;
#ifdef WIN32
	DWORD dwBytesWritten;
#endif

#ifndef WIN32
	n = write(fd, buffer->buffer, buffer->off);
	if (n == -1)
		return (-1);
	if (n == 0)
		return (0);
#else
	n = WriteFile((HANDLE)fd, buffer->buffer, buffer->off, &dwBytesWritten, NULL);
	if (n == 0)
		return (-1);
	if (dwBytesWritten == 0)
		return (0);
	n = dwBytesWritten;
#endif
	evbuffer_drain(buffer, n);

	return (n);
}