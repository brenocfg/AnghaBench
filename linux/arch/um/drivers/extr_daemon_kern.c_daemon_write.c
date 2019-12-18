#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uml_net_private {int /*<<< orphan*/  user; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct daemon_data {int dummy; } ;

/* Variables and functions */
 int daemon_user_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct daemon_data*) ; 

__attribute__((used)) static int daemon_write(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return daemon_user_write(fd, skb->data, skb->len,
				 (struct daemon_data *) &lp->user);
}