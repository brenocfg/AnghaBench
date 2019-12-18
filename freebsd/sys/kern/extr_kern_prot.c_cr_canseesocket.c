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
struct socket {int /*<<< orphan*/  so_cred; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ cr_canseeothergids (struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ cr_canseeotheruids (struct ucred*,int /*<<< orphan*/ ) ; 
 int mac_socket_check_visible (struct ucred*,struct socket*) ; 
 int prison_check (struct ucred*,int /*<<< orphan*/ ) ; 

int
cr_canseesocket(struct ucred *cred, struct socket *so)
{
	int error;

	error = prison_check(cred, so->so_cred);
	if (error)
		return (ENOENT);
#ifdef MAC
	error = mac_socket_check_visible(cred, so);
	if (error)
		return (error);
#endif
	if (cr_canseeotheruids(cred, so->so_cred))
		return (ENOENT);
	if (cr_canseeothergids(cred, so->so_cred))
		return (ENOENT);

	return (0);
}