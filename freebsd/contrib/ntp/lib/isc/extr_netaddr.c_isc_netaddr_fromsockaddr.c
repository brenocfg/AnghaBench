#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * sun_path; } ;
struct TYPE_13__ {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_11__ {int sa_family; } ;
struct TYPE_16__ {TYPE_5__ sunix; TYPE_3__ sin6; TYPE_2__ sin; TYPE_1__ sa; } ;
struct TYPE_17__ {TYPE_6__ type; } ;
typedef  TYPE_7__ isc_sockaddr_t ;
struct TYPE_14__ {int /*<<< orphan*/ * un; int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_18__ {int family; int /*<<< orphan*/  zone; TYPE_4__ type; } ;
typedef  TYPE_8__ isc_netaddr_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
isc_netaddr_fromsockaddr(isc_netaddr_t *t, const isc_sockaddr_t *s) {
	int family = s->type.sa.sa_family;
	t->family = family;
	switch (family) {
	case AF_INET:
		t->type.in = s->type.sin.sin_addr;
		t->zone = 0;
		break;
	case AF_INET6:
		memcpy(&t->type.in6, &s->type.sin6.sin6_addr, 16);
#ifdef ISC_PLATFORM_HAVESCOPEID
		t->zone = s->type.sin6.sin6_scope_id;
#else
		t->zone = 0;
#endif
		break;
#ifdef ISC_PLATFORM_HAVESYSUNH
	case AF_UNIX:
		memcpy(t->type.un, s->type.sunix.sun_path, sizeof(t->type.un));
		t->zone = 0;
		break;
#endif
	default:
		INSIST(0);
	}
}