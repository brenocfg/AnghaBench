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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  ifid; } ;
struct TYPE_4__ {TYPE_1__ ipv6; } ;
struct radacct {TYPE_2__ peer; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_IPV6CP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
radius_Account_Set_Ipv6(struct radacct *ac, u_char *ifid)
{
  ac->proto = PROTO_IPV6CP;
  memcpy(&ac->peer.ipv6.ifid, ifid, sizeof(ac->peer.ipv6.ifid));
}