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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  rtable ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RTABLE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* sys_get_rdomain (int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 

char *
get_rdomain(int fd)
{
#if defined(HAVE_SYS_GET_RDOMAIN)
	return sys_get_rdomain(fd);
#elif defined(__OpenBSD__)
	int rtable;
	char *ret;
	socklen_t len = sizeof(rtable);

	if (getsockopt(fd, SOL_SOCKET, SO_RTABLE, &rtable, &len) == -1) {
		error("Failed to get routing domain for fd %d: %s",
		    fd, strerror(errno));
		return NULL;
	}
	xasprintf(&ret, "%d", rtable);
	return ret;
#else /* defined(__OpenBSD__) */
	return NULL;
#endif
}