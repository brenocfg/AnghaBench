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
struct sockaddr_un {char* sun_path; } ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 scalar_t__ _getsockname (int,struct sockaddr*,int*) ; 

int
__rpc_sockisbound(int fd)
{
	struct sockaddr_storage ss;
	socklen_t slen;

	slen = sizeof (struct sockaddr_storage);
	if (_getsockname(fd, (struct sockaddr *)(void *)&ss, &slen) < 0)
		return 0;

	switch (ss.ss_family) {
		case AF_INET:
			return (((struct sockaddr_in *)
			    (void *)&ss)->sin_port != 0);
#ifdef INET6
		case AF_INET6:
			return (((struct sockaddr_in6 *)
			    (void *)&ss)->sin6_port != 0);
#endif
		case AF_LOCAL:
			/* XXX check this */
			return (((struct sockaddr_un *)
			    (void *)&ss)->sun_path[0] != '\0');
		default:
			break;
	}

	return 0;
}