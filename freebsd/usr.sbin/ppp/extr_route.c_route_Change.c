#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ncpaddr {int dummy; } ;
struct sticky_route {int type; struct ncpaddr gw; int /*<<< orphan*/  dst; struct sticky_route* next; } ;
struct TYPE_6__ {TYPE_1__* dns; } ;
struct TYPE_7__ {TYPE_2__ ns; } ;
struct TYPE_8__ {TYPE_3__ ipcp; } ;
struct bundle {TYPE_4__ ncp; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ INADDR_NONE ; 
 int ROUTE_DSTDNS0 ; 
 int ROUTE_DSTDNS1 ; 
 int ROUTE_DSTHISADDR ; 
 int ROUTE_DSTHISADDR6 ; 
 int ROUTE_DSTMYADDR ; 
 int ROUTE_DSTMYADDR6 ; 
 int ROUTE_GWHISADDR ; 
 int ROUTE_GWHISADDR6 ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  ncpaddr_copy (struct ncpaddr*,struct ncpaddr const*) ; 
 int /*<<< orphan*/  ncpaddr_equal (struct ncpaddr*,struct ncpaddr const*) ; 
 scalar_t__ ncpaddr_family (struct ncpaddr const*) ; 
 int /*<<< orphan*/  ncprange_getaddr (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_sethost (int /*<<< orphan*/ *,struct ncpaddr const*) ; 
 int /*<<< orphan*/  rt_Set (struct bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncpaddr*,int,int /*<<< orphan*/ ) ; 

void
route_Change(struct bundle *bundle, struct sticky_route *r,
             const struct ncpaddr *me, const struct ncpaddr *peer)
{
  struct ncpaddr dst;

  for (; r; r = r->next) {
    ncprange_getaddr(&r->dst, &dst);
    if (ncpaddr_family(me) == AF_INET) {
      if ((r->type & ROUTE_DSTMYADDR) && !ncpaddr_equal(&dst, me)) {
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        ncprange_sethost(&r->dst, me);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_DSTHISADDR) && !ncpaddr_equal(&dst, peer)) {
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        ncprange_sethost(&r->dst, peer);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_DSTDNS0) && !ncpaddr_equal(&dst, peer)) {
        if (bundle->ncp.ipcp.ns.dns[0].s_addr == INADDR_NONE)
          continue;
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_DSTDNS1) && !ncpaddr_equal(&dst, peer)) {
        if (bundle->ncp.ipcp.ns.dns[1].s_addr == INADDR_NONE)
          continue;
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_GWHISADDR) && !ncpaddr_equal(&r->gw, peer))
        ncpaddr_copy(&r->gw, peer);
#ifndef NOINET6
    } else if (ncpaddr_family(me) == AF_INET6) {
      if ((r->type & ROUTE_DSTMYADDR6) && !ncpaddr_equal(&dst, me)) {
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        ncprange_sethost(&r->dst, me);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_DSTHISADDR6) && !ncpaddr_equal(&dst, peer)) {
        rt_Set(bundle, RTM_DELETE, &r->dst, NULL, 1, 0);
        ncprange_sethost(&r->dst, peer);
        if (r->type & ROUTE_GWHISADDR)
          ncpaddr_copy(&r->gw, peer);
      } else if ((r->type & ROUTE_GWHISADDR6) && !ncpaddr_equal(&r->gw, peer))
        ncpaddr_copy(&r->gw, peer);
#endif
    }
    rt_Set(bundle, RTM_ADD, &r->dst, &r->gw, 1, 0);
  }
}