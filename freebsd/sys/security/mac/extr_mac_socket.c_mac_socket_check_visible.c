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
struct ucred {int dummy; } ;
struct socket {int /*<<< orphan*/  so_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct socket*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_check_visible ; 

int
mac_socket_check_visible(struct ucred *cred, struct socket *so)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(socket_check_visible, cred, so,
	    so->so_label);
	MAC_CHECK_PROBE2(socket_check_visible, error, cred, so);

	return (error);
}