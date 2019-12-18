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
struct sockaddr_un {int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ESOCKTNOSUPPORT ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 int convert_in_un_alloc (struct socket_info*,struct sockaddr const*,struct sockaddr_un*,int*) ; 
 int convert_in_un_remote (struct socket_info*,struct sockaddr const*,struct sockaddr_un*,int*) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int sockaddr_convert_to_un(struct socket_info *si, const struct sockaddr *in_addr, socklen_t in_len,
				  struct sockaddr_un *out_addr, int alloc_sock, int *bcast)
{
	if (!out_addr)
		return 0;

	out_addr->sun_family = AF_UNIX;

	switch (in_addr->sa_family) {
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
		if (alloc_sock) {
			return convert_in_un_alloc(si, in_addr, out_addr, bcast);
		} else {
			return convert_in_un_remote(si, in_addr, out_addr, bcast);
		}
	default:
		break;
	}

	errno = EAFNOSUPPORT;
	return -1;
}