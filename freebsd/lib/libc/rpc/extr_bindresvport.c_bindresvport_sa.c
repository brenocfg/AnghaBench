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
typedef  scalar_t__ u_int16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {int sa_family; int sa_len; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  portlow ;
typedef  int /*<<< orphan*/  old ;
typedef  int /*<<< orphan*/  myaddr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EPFNOSUPPORT ; 
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPV6_PORTRANGE ; 
 int IPV6_PORTRANGE_LOW ; 
 int IP_PORTRANGE ; 
 int IP_PORTRANGE_LOW ; 
 int _bind (int,struct sockaddr*,int) ; 
 int _getsockname (int,struct sockaddr*,int*) ; 
 int _getsockopt (int,int,int,int*,int*) ; 
 int _setsockopt (int,int,int,int*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 

int
bindresvport_sa(int sd, struct sockaddr *sa)
{
	int old, error, af;
	struct sockaddr_storage myaddr;
	struct sockaddr_in *sin;
#ifdef INET6
	struct sockaddr_in6 *sin6;
#endif
	int proto, portrange, portlow;
	u_int16_t *portp;
	socklen_t salen;

	if (sa == NULL) {
		salen = sizeof(myaddr);
		sa = (struct sockaddr *)&myaddr;

		if (_getsockname(sd, sa, &salen) == -1)
			return -1;	/* errno is correctly set */

		af = sa->sa_family;
		memset(sa, 0, salen);
	} else
		af = sa->sa_family;

	switch (af) {
	case AF_INET:
		proto = IPPROTO_IP;
		portrange = IP_PORTRANGE;
		portlow = IP_PORTRANGE_LOW;
		sin = (struct sockaddr_in *)sa;
		salen = sizeof(struct sockaddr_in);
		portp = &sin->sin_port;
		break;
#ifdef INET6
	case AF_INET6:
		proto = IPPROTO_IPV6;
		portrange = IPV6_PORTRANGE;
		portlow = IPV6_PORTRANGE_LOW;
		sin6 = (struct sockaddr_in6 *)sa;
		salen = sizeof(struct sockaddr_in6);
		portp = &sin6->sin6_port;
		break;
#endif
	default:
		errno = EPFNOSUPPORT;
		return (-1);
	}
	sa->sa_family = af;
	sa->sa_len = salen;

	if (*portp == 0) {
		socklen_t oldlen = sizeof(old);

		error = _getsockopt(sd, proto, portrange, &old, &oldlen);
		if (error < 0)
			return (error);

		error = _setsockopt(sd, proto, portrange, &portlow,
		    sizeof(portlow));
		if (error < 0)
			return (error);
	}

	error = _bind(sd, sa, salen);

	if (*portp == 0) {
		int saved_errno = errno;

		if (error < 0) {
			if (_setsockopt(sd, proto, portrange, &old,
			    sizeof(old)) < 0)
				errno = saved_errno;
			return (error);
		}

		if (sa != (struct sockaddr *)&myaddr) {
			/* Hmm, what did the kernel assign? */
			if (_getsockname(sd, sa, &salen) < 0)
				errno = saved_errno;
			return (error);
		}
	}
	return (error);
}