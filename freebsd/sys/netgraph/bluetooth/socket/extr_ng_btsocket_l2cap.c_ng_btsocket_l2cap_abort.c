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
struct socket {int /*<<< orphan*/  so_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_disconnect (struct socket*) ; 

void
ng_btsocket_l2cap_abort(struct socket *so)
{
	so->so_error = ECONNABORTED;

	(void)ng_btsocket_l2cap_disconnect(so);
}