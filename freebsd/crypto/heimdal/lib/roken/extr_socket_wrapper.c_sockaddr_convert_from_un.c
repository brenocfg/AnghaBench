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
struct socket_info {int /*<<< orphan*/  type; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ESOCKTNOSUPPORT ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 int convert_un_in (struct sockaddr_un const*,struct sockaddr*,scalar_t__*) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int sockaddr_convert_from_un(const struct socket_info *si,
				    const struct sockaddr_un *in_addr,
				    socklen_t un_addrlen,
				    int family,
				    struct sockaddr *out_addr,
				    socklen_t *out_addrlen)
{
	if (out_addr == NULL || out_addrlen == NULL)
		return 0;

	if (un_addrlen == 0) {
		*out_addrlen = 0;
		return 0;
	}

	switch (family) {
	case AF_INET:
#ifdef HAVE_IPV6
	case AF_INET6:
#endif
		switch (si->type) {
		case SOCK_STREAM:
		case SOCK_DGRAM:
			break;
		default:
			errno = ESOCKTNOSUPPORT;
			return -1;
		}
		return convert_un_in(in_addr, out_addr, out_addrlen);
	default:
		break;
	}

	errno = EAFNOSUPPORT;
	return -1;
}