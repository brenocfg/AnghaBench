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
struct xaddr {int af; int /*<<< orphan*/  scope_id; int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xaddr*,char,int) ; 

__attribute__((used)) static int
addr_sa_to_xaddr(struct sockaddr *sa, socklen_t slen, struct xaddr *xa)
{
	struct sockaddr_in *in4 = (struct sockaddr_in *)sa;
	struct sockaddr_in6 *in6 = (struct sockaddr_in6 *)sa;

	memset(xa, '\0', sizeof(*xa));

	switch (sa->sa_family) {
	case AF_INET:
		if (slen < (socklen_t)sizeof(*in4))
			return -1;
		xa->af = AF_INET;
		memcpy(&xa->v4, &in4->sin_addr, sizeof(xa->v4));
		break;
	case AF_INET6:
		if (slen < (socklen_t)sizeof(*in6))
			return -1;
		xa->af = AF_INET6;
		memcpy(&xa->v6, &in6->sin6_addr, sizeof(xa->v6));
#ifdef HAVE_STRUCT_SOCKADDR_IN6_SIN6_SCOPE_ID
		xa->scope_id = in6->sin6_scope_id;
#endif
		break;
	default:
		return -1;
	}

	return 0;
}