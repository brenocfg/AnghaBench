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
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * ng_btsocket_sco_node ; 
 int ng_btsocket_sco_peeraddr (struct socket*,struct sockaddr**) ; 

int
ng_btsocket_sco_accept(struct socket *so, struct sockaddr **nam)
{
	if (ng_btsocket_sco_node == NULL) 
		return (EINVAL);

	return (ng_btsocket_sco_peeraddr(so, nam));
}