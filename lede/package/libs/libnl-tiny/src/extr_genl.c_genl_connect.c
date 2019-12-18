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
struct nl_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_GENERIC ; 
 int nl_connect (struct nl_sock*,int /*<<< orphan*/ ) ; 

int genl_connect(struct nl_sock *sk)
{
	return nl_connect(sk, NETLINK_GENERIC);
}