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
struct socket {int /*<<< orphan*/  so_peerlabel; int /*<<< orphan*/  so_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ mac_policy_count ; 
 int /*<<< orphan*/  socketpeer_set_from_socket ; 

void
mac_socketpeer_set_from_socket(struct socket *oldso, struct socket *newso)
{
	
	if (mac_policy_count == 0)
		return;

	MAC_POLICY_PERFORM_NOSLEEP(socketpeer_set_from_socket, oldso,
	    oldso->so_label, newso, newso->so_peerlabel);
}