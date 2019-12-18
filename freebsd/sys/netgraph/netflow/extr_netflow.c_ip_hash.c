#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct flow_rec {int r_ip_p; TYPE_2__ r_dst; TYPE_1__ r_src; int /*<<< orphan*/  r_dport; int /*<<< orphan*/  r_sport; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FULL_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 

__attribute__((used)) static inline uint32_t
ip_hash(struct flow_rec *r)
{

	switch (r->r_ip_p) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
		return FULL_HASH(r->r_src.s_addr, r->r_dst.s_addr,
		    r->r_sport, r->r_dport);
	default:
		return ADDR_HASH(r->r_src.s_addr, r->r_dst.s_addr);
	}
}