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
struct TYPE_3__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ ip; } ;
struct radacct {TYPE_2__ peer; int /*<<< orphan*/  proto; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_IPCP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 

void
radius_Account_Set_Ip(struct radacct *ac, struct in_addr *peer_ip,
		      struct in_addr *netmask)
{
  ac->proto = PROTO_IPCP;
  memcpy(&ac->peer.ip.addr, peer_ip, sizeof(ac->peer.ip.addr));
  memcpy(&ac->peer.ip.mask, netmask, sizeof(ac->peer.ip.mask));
}