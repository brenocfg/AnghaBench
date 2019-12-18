#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * addr32; } ;
struct TYPE_7__ {TYPE_5__ mask; TYPE_5__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  tblname; TYPE_1__ a; int /*<<< orphan*/  ifname; } ;
struct TYPE_9__ {int type; TYPE_2__ v; int /*<<< orphan*/  iflags; } ;
struct TYPE_10__ {scalar_t__ neg; TYPE_3__ addr; } ;
struct pf_rule {TYPE_4__ src; } ;

/* Variables and functions */
#define  PF_ADDR_ADDRMASK 132 
#define  PF_ADDR_DYNIFTL 131 
#define  PF_ADDR_NOROUTE 130 
#define  PF_ADDR_TABLE 129 
#define  PF_ADDR_URPFFAILED 128 
 int /*<<< orphan*/  memcmp (TYPE_5__*,TYPE_5__*,int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
skip_cmp_src_addr(struct pf_rule *a, struct pf_rule *b)
{
	if (a->src.neg != b->src.neg ||
	    a->src.addr.type != b->src.addr.type)
		return (1);
	/* XXX if (a->proto != b->proto && a->proto != 0 && b->proto != 0
	 *    && (a->proto == IPPROTO_TCP || a->proto == IPPROTO_UDP ||
	 *    a->proto == IPPROTO_ICMP
	 *	return (1);
	 */
	switch (a->src.addr.type) {
	case PF_ADDR_ADDRMASK:
		if (memcmp(&a->src.addr.v.a.addr, &b->src.addr.v.a.addr,
		    sizeof(a->src.addr.v.a.addr)) ||
		    memcmp(&a->src.addr.v.a.mask, &b->src.addr.v.a.mask,
		    sizeof(a->src.addr.v.a.mask)) ||
		    (a->src.addr.v.a.addr.addr32[0] == 0 &&
		    a->src.addr.v.a.addr.addr32[1] == 0 &&
		    a->src.addr.v.a.addr.addr32[2] == 0 &&
		    a->src.addr.v.a.addr.addr32[3] == 0))
			return (1);
		return (0);
	case PF_ADDR_DYNIFTL:
		if (strcmp(a->src.addr.v.ifname, b->src.addr.v.ifname) != 0 ||
		    a->src.addr.iflags != b->src.addr.iflags ||
		    memcmp(&a->src.addr.v.a.mask, &b->src.addr.v.a.mask,
		    sizeof(a->src.addr.v.a.mask)))
			return (1);
		return (0);
	case PF_ADDR_NOROUTE:
	case PF_ADDR_URPFFAILED:
		return (0);
	case PF_ADDR_TABLE:
		return (strcmp(a->src.addr.v.tblname, b->src.addr.v.tblname));
	}
	return (1);
}