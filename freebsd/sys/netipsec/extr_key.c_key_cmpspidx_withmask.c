#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct TYPE_8__ {int sa_family; scalar_t__ sa_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_9__ {TYPE_3__ sa; TYPE_2__ sin6; TYPE_1__ sin; } ;
struct secpolicyindex {scalar_t__ ul_proto; TYPE_4__ dst; int /*<<< orphan*/  prefd; TYPE_4__ src; int /*<<< orphan*/  prefs; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IPSEC_PORT_ANY ; 
 scalar_t__ IPSEC_ULPROTO_ANY ; 
 int /*<<< orphan*/  bcmp (TYPE_4__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  key_bbcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
key_cmpspidx_withmask(struct secpolicyindex *spidx0,
    struct secpolicyindex *spidx1)
{
	/* sanity */
	if (spidx0 == NULL && spidx1 == NULL)
		return 1;

	if (spidx0 == NULL || spidx1 == NULL)
		return 0;

	if (spidx0->src.sa.sa_family != spidx1->src.sa.sa_family ||
	    spidx0->dst.sa.sa_family != spidx1->dst.sa.sa_family ||
	    spidx0->src.sa.sa_len != spidx1->src.sa.sa_len ||
	    spidx0->dst.sa.sa_len != spidx1->dst.sa.sa_len)
		return 0;

	/* if spidx.ul_proto == IPSEC_ULPROTO_ANY, ignore. */
	if (spidx0->ul_proto != (u_int16_t)IPSEC_ULPROTO_ANY
	 && spidx0->ul_proto != spidx1->ul_proto)
		return 0;

	switch (spidx0->src.sa.sa_family) {
	case AF_INET:
		if (spidx0->src.sin.sin_port != IPSEC_PORT_ANY
		 && spidx0->src.sin.sin_port != spidx1->src.sin.sin_port)
			return 0;
		if (!key_bbcmp(&spidx0->src.sin.sin_addr,
		    &spidx1->src.sin.sin_addr, spidx0->prefs))
			return 0;
		break;
	case AF_INET6:
		if (spidx0->src.sin6.sin6_port != IPSEC_PORT_ANY
		 && spidx0->src.sin6.sin6_port != spidx1->src.sin6.sin6_port)
			return 0;
		/*
		 * scope_id check. if sin6_scope_id is 0, we regard it
		 * as a wildcard scope, which matches any scope zone ID. 
		 */
		if (spidx0->src.sin6.sin6_scope_id &&
		    spidx1->src.sin6.sin6_scope_id &&
		    spidx0->src.sin6.sin6_scope_id != spidx1->src.sin6.sin6_scope_id)
			return 0;
		if (!key_bbcmp(&spidx0->src.sin6.sin6_addr,
		    &spidx1->src.sin6.sin6_addr, spidx0->prefs))
			return 0;
		break;
	default:
		/* XXX */
		if (bcmp(&spidx0->src, &spidx1->src, spidx0->src.sa.sa_len) != 0)
			return 0;
		break;
	}

	switch (spidx0->dst.sa.sa_family) {
	case AF_INET:
		if (spidx0->dst.sin.sin_port != IPSEC_PORT_ANY
		 && spidx0->dst.sin.sin_port != spidx1->dst.sin.sin_port)
			return 0;
		if (!key_bbcmp(&spidx0->dst.sin.sin_addr,
		    &spidx1->dst.sin.sin_addr, spidx0->prefd))
			return 0;
		break;
	case AF_INET6:
		if (spidx0->dst.sin6.sin6_port != IPSEC_PORT_ANY
		 && spidx0->dst.sin6.sin6_port != spidx1->dst.sin6.sin6_port)
			return 0;
		/*
		 * scope_id check. if sin6_scope_id is 0, we regard it
		 * as a wildcard scope, which matches any scope zone ID. 
		 */
		if (spidx0->dst.sin6.sin6_scope_id &&
		    spidx1->dst.sin6.sin6_scope_id &&
		    spidx0->dst.sin6.sin6_scope_id != spidx1->dst.sin6.sin6_scope_id)
			return 0;
		if (!key_bbcmp(&spidx0->dst.sin6.sin6_addr,
		    &spidx1->dst.sin6.sin6_addr, spidx0->prefd))
			return 0;
		break;
	default:
		/* XXX */
		if (bcmp(&spidx0->dst, &spidx1->dst, spidx0->dst.sa.sa_len) != 0)
			return 0;
		break;
	}

	/* XXX Do we check other field ?  e.g. flowinfo */

	return 1;
}