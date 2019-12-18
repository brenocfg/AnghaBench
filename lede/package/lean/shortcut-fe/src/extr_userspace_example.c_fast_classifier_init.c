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

/* Variables and functions */
 int /*<<< orphan*/  FAST_CLASSIFIER_GENL_MCGRP ; 
 int /*<<< orphan*/  FAST_CLASSIFIER_GENL_NAME ; 
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_VALID ; 
 scalar_t__ family ; 
 int /*<<< orphan*/  genl_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ genl_ctrl_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ genl_ctrl_resolve_grp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ grp_id ; 
 int /*<<< orphan*/  nl_close (int /*<<< orphan*/ ) ; 
 int nl_socket_add_membership (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nl_socket_alloc () ; 
 int /*<<< orphan*/  nl_socket_disable_seq_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_socket_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_socket_modify_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_cb ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  sock_event ; 

int fast_classifier_init(void)
{
	int err;

	sock = nl_socket_alloc();
	if (!sock) {
		printf("Unable to allocation socket.\n");
		return -1;
	}
	genl_connect(sock);

	sock_event = nl_socket_alloc();
	if (!sock_event) {
		nl_close(sock);
		nl_socket_free(sock);
		printf("Unable to allocation socket.\n");
		return -1;
	}
	genl_connect(sock_event);

	family = genl_ctrl_resolve(sock, FAST_CLASSIFIER_GENL_NAME);
	if (family < 0) {
		nl_close(sock_event);
		nl_close(sock);
		nl_socket_free(sock);
		nl_socket_free(sock_event);
		printf("Unable to resolve family\n");
		return -1;
	}

	grp_id = genl_ctrl_resolve_grp(sock, FAST_CLASSIFIER_GENL_NAME,
				       FAST_CLASSIFIER_GENL_MCGRP);
	if (grp_id < 0) {
		printf("Unable to resolve mcast group\n");
		return -1;
	}

	err = nl_socket_add_membership(sock_event, grp_id);
	if (err < 0) {
		printf("Unable to add membership\n");
		return -1;
	}

	nl_socket_disable_seq_check(sock_event);
	nl_socket_modify_cb(sock_event, NL_CB_VALID, NL_CB_CUSTOM, parse_cb, NULL);

	return 0;
}