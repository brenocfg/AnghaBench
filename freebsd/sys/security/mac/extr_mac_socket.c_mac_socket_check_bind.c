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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct socket*,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  socket_check_bind ; 

int
mac_socket_check_bind(struct ucred *cred, struct socket *so,
    struct sockaddr *sa)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(socket_check_bind, cred, so, so->so_label,
	    sa);
	MAC_CHECK_PROBE3(socket_check_bind, error, cred, so, sa);

	return (error);
}