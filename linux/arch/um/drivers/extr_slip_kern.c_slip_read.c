#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uml_net_private {int /*<<< orphan*/  user; } ;
struct slip_data {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int slip_user_read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct slip_data*) ; 

__attribute__((used)) static int slip_read(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return slip_user_read(fd, skb_mac_header(skb), skb->dev->mtu,
			      (struct slip_data *) &lp->user);
}