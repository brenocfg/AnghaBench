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
struct unl {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int nl_socket_drop_membership (int /*<<< orphan*/ ,int) ; 
 int unl_genl_multicast_id (struct unl*,char const*) ; 

int unl_genl_unsubscribe(struct unl *unl, const char *name)
{
	int mcid;

	mcid = unl_genl_multicast_id(unl, name);
	if (mcid < 0)
		return mcid;

	return nl_socket_drop_membership(unl->sock, mcid);
}