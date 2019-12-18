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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int EVBUFFER_MAX_READ ; 
 int /*<<< orphan*/  FIONREAD ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int
get_n_bytes_readable_on_socket(evutil_socket_t fd)
{
#if defined(FIONREAD) && defined(_WIN32)
	unsigned long lng = EVBUFFER_MAX_READ;
	if (ioctlsocket(fd, FIONREAD, &lng) < 0)
		return -1;
	/* Can overflow, but mostly harmlessly. XXXX */
	return (int)lng;
#elif defined(FIONREAD)
	int n = EVBUFFER_MAX_READ;
	if (ioctl(fd, FIONREAD, &n) < 0)
		return -1;
	return n;
#else
	return EVBUFFER_MAX_READ;
#endif
}