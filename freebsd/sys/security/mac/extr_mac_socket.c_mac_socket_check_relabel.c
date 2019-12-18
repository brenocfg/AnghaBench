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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct socket*,struct label*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct socket*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int /*<<< orphan*/  socket_check_relabel ; 

__attribute__((used)) static int
mac_socket_check_relabel(struct ucred *cred, struct socket *so,
    struct label *newlabel)
{
	int error;

	SOCK_LOCK_ASSERT(so);

	MAC_POLICY_CHECK_NOSLEEP(socket_check_relabel, cred, so,
	    so->so_label, newlabel);
	MAC_CHECK_PROBE3(socket_check_relabel, error, cred, so, newlabel);

	return (error);
}