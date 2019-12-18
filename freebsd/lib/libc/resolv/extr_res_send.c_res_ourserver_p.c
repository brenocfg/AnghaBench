#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int sa_family; } ;
typedef  TYPE_2__* res_state ;
struct TYPE_9__ {int /*<<< orphan*/ * ext; } ;
struct TYPE_8__ {int nscount; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 TYPE_5__ EXT (TYPE_2__* const) ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ get_nsaddr (TYPE_2__* const,int) ; 

int
res_ourserver_p(const res_state statp, const struct sockaddr *sa) {
	const struct sockaddr_in *inp, *srv;
	const struct sockaddr_in6 *in6p, *srv6;
	int ns;

	switch (sa->sa_family) {
	case AF_INET:
		inp = (const struct sockaddr_in *)sa;
		for (ns = 0;  ns < statp->nscount;  ns++) {
			srv = (struct sockaddr_in *)get_nsaddr(statp, ns);
			if (srv->sin_family == inp->sin_family &&
			    srv->sin_port == inp->sin_port &&
			    (srv->sin_addr.s_addr == INADDR_ANY ||
			     srv->sin_addr.s_addr == inp->sin_addr.s_addr))
				return (1);
		}
		break;
	case AF_INET6:
		if (EXT(statp).ext == NULL)
			break;
		in6p = (const struct sockaddr_in6 *)sa;
		for (ns = 0;  ns < statp->nscount;  ns++) {
			srv6 = (struct sockaddr_in6 *)get_nsaddr(statp, ns);
			if (srv6->sin6_family == in6p->sin6_family &&
			    srv6->sin6_port == in6p->sin6_port &&
#ifdef HAVE_SIN6_SCOPE_ID
			    (srv6->sin6_scope_id == 0 ||
			     srv6->sin6_scope_id == in6p->sin6_scope_id) &&
#endif
			    (IN6_IS_ADDR_UNSPECIFIED(&srv6->sin6_addr) ||
			     IN6_ARE_ADDR_EQUAL(&srv6->sin6_addr, &in6p->sin6_addr)))
				return (1);
		}
		break;
	default:
		break;
	}
	return (0);
}