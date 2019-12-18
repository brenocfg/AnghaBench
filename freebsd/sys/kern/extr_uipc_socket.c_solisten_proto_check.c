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
struct socket {int so_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 

int
solisten_proto_check(struct socket *so)
{

	SOCK_LOCK_ASSERT(so);

	if (so->so_state & (SS_ISCONNECTED | SS_ISCONNECTING |
	    SS_ISDISCONNECTING))
		return (EINVAL);
	return (0);
}