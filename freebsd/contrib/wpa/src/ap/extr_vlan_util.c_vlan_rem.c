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
struct rtnl_link {int dummy; } ;
struct nl_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  NETLINK_ROUTE ; 
 int nl_connect (struct nl_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_geterror (int) ; 
 struct nl_sock* nl_socket_alloc () ; 
 int /*<<< orphan*/  nl_socket_free (struct nl_sock*) ; 
 int rtnl_link_delete (struct nl_sock*,struct rtnl_link*) ; 
 int rtnl_link_get_kernel (struct nl_sock*,int /*<<< orphan*/ ,char const*,struct rtnl_link**) ; 
 int /*<<< orphan*/  rtnl_link_put (struct rtnl_link*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int vlan_rem(const char *if_name)
{
	int err, ret = -1;
	struct nl_sock *handle = NULL;
	struct rtnl_link *rlink = NULL;

	wpa_printf(MSG_DEBUG, "VLAN: vlan_rem(if_name=%s)", if_name);

	handle = nl_socket_alloc();
	if (!handle) {
		wpa_printf(MSG_ERROR, "VLAN: failed to open netlink socket");
		goto vlan_rem_error;
	}

	err = nl_connect(handle, NETLINK_ROUTE);
	if (err < 0) {
		wpa_printf(MSG_ERROR, "VLAN: failed to connect to netlink: %s",
			   nl_geterror(err));
		goto vlan_rem_error;
	}

	err = rtnl_link_get_kernel(handle, 0, if_name, &rlink);
	if (err < 0) {
		/* link does not exist */
		wpa_printf(MSG_ERROR, "VLAN: interface %s does not exists",
			   if_name);
		goto vlan_rem_error;
	}

	err = rtnl_link_delete(handle, rlink);
	if (err < 0) {
		wpa_printf(MSG_ERROR, "VLAN: failed to remove link %s: %s",
			   if_name, nl_geterror(err));
		goto vlan_rem_error;
	}

	ret = 0;

vlan_rem_error:
	if (rlink)
		rtnl_link_put(rlink);
	if (handle)
		nl_socket_free(handle);
	return ret;
}