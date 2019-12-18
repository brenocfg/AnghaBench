#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rt_entry {scalar_t__ rt_dst; scalar_t__ rt_mask; } ;
typedef  scalar_t__ naddr ;
struct TYPE_14__ {scalar_t__ (* rnh_lookup ) (TYPE_3__*,TYPE_4__*,TYPE_5__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_2__ sin_addr; } ;
struct TYPE_10__ {scalar_t__ s_addr; } ;
struct TYPE_12__ {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 TYPE_3__ dst_sock ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 TYPE_4__ mask_sock ; 
 int /*<<< orphan*/  masktrim (TYPE_4__*) ; 
 TYPE_5__* rhead ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*,TYPE_5__*) ; 

struct rt_entry *
rtget(naddr dst, naddr mask)
{
	struct rt_entry *rt;

	dst_sock.sin_addr.s_addr = dst;
	mask_sock.sin_addr.s_addr = htonl(mask);
	masktrim(&mask_sock);
	rt = (struct rt_entry *)rhead->rnh_lookup(&dst_sock,&mask_sock,rhead);
	if (!rt
	    || rt->rt_dst != dst
	    || rt->rt_mask != mask)
		return 0;

	return rt;
}