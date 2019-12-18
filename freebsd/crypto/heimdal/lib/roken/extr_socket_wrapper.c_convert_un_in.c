#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {char* sun_path; } ;
struct TYPE_4__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {void* sin6_port; TYPE_2__ sin6_addr; int /*<<< orphan*/  sin6_family; void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {void* sin6_port; TYPE_2__ sin6_addr; int /*<<< orphan*/  sin6_family; void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int MAX_WRAPPED_INTERFACES ; 
 int /*<<< orphan*/  SOCKET_FORMAT ; 
#define  SOCKET_TYPE_CHAR_TCP 131 
#define  SOCKET_TYPE_CHAR_TCP_V6 130 
#define  SOCKET_TYPE_CHAR_UDP 129 
#define  SOCKET_TYPE_CHAR_UDP_V6 128 
 int /*<<< orphan*/  SW_IPV6_ADDRESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htonl (int) ; 
 void* htons (unsigned int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int convert_un_in(const struct sockaddr_un *un, struct sockaddr *in, socklen_t *len)
{
	unsigned int iface;
	unsigned int prt;
	const char *p;
	char type;

	p = strrchr(un->sun_path, '/');
	if (p) p++; else p = un->sun_path;

	if (sscanf(p, SOCKET_FORMAT, &type, &iface, &prt) != 3) {
		errno = EINVAL;
		return -1;
	}

	if (iface == 0 || iface > MAX_WRAPPED_INTERFACES) {
		errno = EINVAL;
		return -1;
	}

	if (prt > 0xFFFF) {
		errno = EINVAL;
		return -1;
	}

	switch(type) {
	case SOCKET_TYPE_CHAR_TCP:
	case SOCKET_TYPE_CHAR_UDP: {
		struct sockaddr_in *in2 = (struct sockaddr_in *)in;

		if ((*len) < sizeof(*in2)) {
		    errno = EINVAL;
		    return -1;
		}

		memset(in2, 0, sizeof(*in2));
		in2->sin_family = AF_INET;
		in2->sin_addr.s_addr = htonl((127<<24) | iface);
		in2->sin_port = htons(prt);

		*len = sizeof(*in2);
		break;
	}
#ifdef HAVE_IPV6
	case SOCKET_TYPE_CHAR_TCP_V6:
	case SOCKET_TYPE_CHAR_UDP_V6: {
		struct sockaddr_in6 *in2 = (struct sockaddr_in6 *)in;

		if ((*len) < sizeof(*in2)) {
			errno = EINVAL;
			return -1;
		}

		memset(in2, 0, sizeof(*in2));
		in2->sin6_family = AF_INET6;
		in2->sin6_addr.s6_addr[0] = SW_IPV6_ADDRESS;
		in2->sin6_port = htons(prt);

		*len = sizeof(*in2);
		break;
	}
#endif
	default:
		errno = EINVAL;
		return -1;
	}

	return 0;
}