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
struct sk_buff {TYPE_4__* dev; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {TYPE_1__ tuntap; } ;
struct TYPE_7__ {TYPE_2__ info; } ;
struct iss_net_private {TYPE_3__ tp; } ;
struct TYPE_8__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_HEADER_OTHER ; 
 int simc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tuntap_read(struct iss_net_private *lp, struct sk_buff **skb)
{
	return simc_read(lp->tp.info.tuntap.fd,
			(*skb)->data, (*skb)->dev->mtu + ETH_HEADER_OTHER);
}