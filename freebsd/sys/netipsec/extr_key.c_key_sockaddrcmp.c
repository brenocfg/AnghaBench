#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; scalar_t__ sa_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcmp (struct sockaddr const*,struct sockaddr const*,int) ; 
 TYPE_3__* satosin (struct sockaddr const*) ; 
 TYPE_2__* satosin6 (struct sockaddr const*) ; 

int
key_sockaddrcmp(const struct sockaddr *sa1, const struct sockaddr *sa2,
    int port)
{
	if (sa1->sa_family != sa2->sa_family || sa1->sa_len != sa2->sa_len)
		return 1;

	switch (sa1->sa_family) {
#ifdef INET
	case AF_INET:
		if (sa1->sa_len != sizeof(struct sockaddr_in))
			return 1;
		if (satosin(sa1)->sin_addr.s_addr !=
		    satosin(sa2)->sin_addr.s_addr) {
			return 1;
		}
		if (port && satosin(sa1)->sin_port != satosin(sa2)->sin_port)
			return 1;
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if (sa1->sa_len != sizeof(struct sockaddr_in6))
			return 1;	/*EINVAL*/
		if (satosin6(sa1)->sin6_scope_id !=
		    satosin6(sa2)->sin6_scope_id) {
			return 1;
		}
		if (!IN6_ARE_ADDR_EQUAL(&satosin6(sa1)->sin6_addr,
		    &satosin6(sa2)->sin6_addr)) {
			return 1;
		}
		if (port &&
		    satosin6(sa1)->sin6_port != satosin6(sa2)->sin6_port) {
			return 1;
		}
		break;
#endif
	default:
		if (bcmp(sa1, sa2, sa1->sa_len) != 0)
			return 1;
		break;
	}

	return 0;
}