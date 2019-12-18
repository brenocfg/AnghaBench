#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  sin6_addr; } ;
struct radix_addr_xentry {int /*<<< orphan*/  value; int /*<<< orphan*/  masklen; TYPE_5__ addr6; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {scalar_t__ sin_family; TYPE_2__ sin_addr; } ;
struct radix_addr_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  masklen; TYPE_3__ addr; } ;
struct in6_addr {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  addr6; TYPE_1__ addr; } ;
struct TYPE_15__ {TYPE_6__ v; scalar_t__ subtype; int /*<<< orphan*/  masklen; TYPE_4__ k; } ;
typedef  TYPE_7__ ipfw_obj_tentry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ta_dump_radix_tentry(void *ta_state, struct table_info *ti, void *e,
    ipfw_obj_tentry *tent)
{
	struct radix_addr_entry *n;
#ifdef INET6
	struct radix_addr_xentry *xn;
#endif

	n = (struct radix_addr_entry *)e;

	/* Guess IPv4/IPv6 radix by sockaddr family */
	if (n->addr.sin_family == AF_INET) {
		tent->k.addr.s_addr = n->addr.sin_addr.s_addr;
		tent->masklen = n->masklen;
		tent->subtype = AF_INET;
		tent->v.kidx = n->value;
#ifdef INET6
	} else {
		xn = (struct radix_addr_xentry *)e;
		memcpy(&tent->k.addr6, &xn->addr6.sin6_addr,
		    sizeof(struct in6_addr));
		tent->masklen = xn->masklen;
		tent->subtype = AF_INET6;
		tent->v.kidx = xn->value;
#endif
	}

	return (0);
}