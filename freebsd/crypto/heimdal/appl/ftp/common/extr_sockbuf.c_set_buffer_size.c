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
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  curr ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int SO_RCVBUF ; 
 int SO_SNDBUF ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int,void*,int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int,void*,int) ; 

void
set_buffer_size(int fd, int read)
{
#if defined(SO_RCVBUF) && defined(SO_SNDBUF) && defined(HAVE_SETSOCKOPT)
    int size = 4194304;
    int optname = read ? SO_RCVBUF : SO_SNDBUF;

#ifdef HAVE_GETSOCKOPT
    int curr=0;
    socklen_t optlen;

    optlen = sizeof(curr);
    if(getsockopt(fd, SOL_SOCKET, optname, (void *)&curr, &optlen) == 0) {
        if(curr >= size) {
            /* Already large enough */
            return;
        }
    }
#endif /* HAVE_GETSOCKOPT */

    while(size >= 131072 &&
	  setsockopt(fd, SOL_SOCKET, optname, (void *)&size, sizeof(size)) < 0)
	size /= 2;
#endif
}