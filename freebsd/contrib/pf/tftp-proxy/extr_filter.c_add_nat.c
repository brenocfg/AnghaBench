#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  void* u_int16_t ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_28__ {void** proxy_port; } ;
struct TYPE_23__ {int /*<<< orphan*/  addr8; } ;
struct TYPE_21__ {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct TYPE_24__ {TYPE_4__ mask; TYPE_2__ addr; } ;
struct TYPE_25__ {TYPE_5__ a; } ;
struct TYPE_26__ {TYPE_6__ v; } ;
struct TYPE_27__ {TYPE_7__ addr; } ;
struct TYPE_22__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_20__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_16__ {TYPE_9__ rpool; } ;
struct TYPE_19__ {TYPE_10__ rule; TYPE_8__ addr; } ;
struct TYPE_18__ {TYPE_1__ sin_addr; } ;
struct TYPE_17__ {TYPE_3__ sin6_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DIOCADDADDR ; 
 int /*<<< orphan*/  DIOCADDRULE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PF_RULESET_NAT ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 TYPE_13__ pfp ; 
 TYPE_13__ pfr ; 
 int prepare_rule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,void*,int /*<<< orphan*/ ) ; 
 TYPE_12__* satosin (struct sockaddr*) ; 
 TYPE_11__* satosin6 (struct sockaddr*) ; 

int
add_nat(u_int32_t id, struct sockaddr *src, struct sockaddr *dst,
    u_int16_t d_port, struct sockaddr *nat, u_int16_t nat_range_low,
    u_int16_t nat_range_high, u_int8_t proto)
{
	if (!src || !dst || !d_port || !nat || !nat_range_low || !proto ||
	    (src->sa_family != nat->sa_family)) {
		errno = EINVAL;
		return (-1);
	}

	if (prepare_rule(id, PF_RULESET_NAT, src, dst, d_port, proto) == -1)
		return (-1);

	if (nat->sa_family == AF_INET) {
		memcpy(&pfp.addr.addr.v.a.addr.v4,
		    &satosin(nat)->sin_addr.s_addr, 4);
		memset(&pfp.addr.addr.v.a.mask.addr8, 255, 4);
	} else {
		memcpy(&pfp.addr.addr.v.a.addr.v6,
		    &satosin6(nat)->sin6_addr.s6_addr, 16);
		memset(&pfp.addr.addr.v.a.mask.addr8, 255, 16);
	}
	if (ioctl(dev, DIOCADDADDR, &pfp) == -1)
		return (-1);

	pfr.rule.rpool.proxy_port[0] = nat_range_low;
	pfr.rule.rpool.proxy_port[1] = nat_range_high;
	if (ioctl(dev, DIOCADDRULE, &pfr) == -1)
		return (-1);

	return (0);
}