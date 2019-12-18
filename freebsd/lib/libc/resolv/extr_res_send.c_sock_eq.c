#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sock_eq(struct sockaddr *a, struct sockaddr *b) {
	struct sockaddr_in *a4, *b4;
	struct sockaddr_in6 *a6, *b6;

	if (a->sa_family != b->sa_family)
		return 0;
	switch (a->sa_family) {
	case AF_INET:
		a4 = (struct sockaddr_in *)a;
		b4 = (struct sockaddr_in *)b;
		return a4->sin_port == b4->sin_port &&
		    a4->sin_addr.s_addr == b4->sin_addr.s_addr;
	case AF_INET6:
		a6 = (struct sockaddr_in6 *)a;
		b6 = (struct sockaddr_in6 *)b;
		return a6->sin6_port == b6->sin6_port &&
#ifdef HAVE_SIN6_SCOPE_ID
		    a6->sin6_scope_id == b6->sin6_scope_id &&
#endif
		    IN6_ARE_ADDR_EQUAL(&a6->sin6_addr, &b6->sin6_addr);
	default:
		return 0;
	}
}