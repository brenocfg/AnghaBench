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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; scalar_t__ sa_len; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int EINVAL ; 

__attribute__((used)) static int
key_checksockaddrs(struct sockaddr *src, struct sockaddr *dst)
{

	/* family match */
	if (src->sa_family != dst->sa_family)
		return (EINVAL);
	/* sa_len match */
	if (src->sa_len != dst->sa_len)
		return (EINVAL);
	switch (src->sa_family) {
#ifdef INET
	case AF_INET:
		if (src->sa_len != sizeof(struct sockaddr_in))
			return (EINVAL);
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if (src->sa_len != sizeof(struct sockaddr_in6))
			return (EINVAL);
		break;
#endif
	default:
		return (EAFNOSUPPORT);
	}
	return (0);
}