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
struct nl_classifier_instance {scalar_t__ family_id; scalar_t__ group_id; int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_VALID ; 
 char* NL_CLASSIFIER_GENL_FAMILY ; 
 char* NL_CLASSIFIER_GENL_GROUP ; 
 int /*<<< orphan*/  genl_connect (int /*<<< orphan*/ *) ; 
 scalar_t__ genl_ctrl_resolve (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ genl_ctrl_resolve_grp (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  nl_classifier_msg_recv ; 
 int /*<<< orphan*/  nl_close (int /*<<< orphan*/ *) ; 
 int nl_socket_add_membership (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * nl_socket_alloc () ; 
 int /*<<< orphan*/  nl_socket_disable_seq_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_socket_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_socket_modify_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int nl_classifier_init(struct nl_classifier_instance *inst)
{
	int ret;

	inst->sock = nl_socket_alloc();
	if (!inst->sock) {
		printf("Unable to allocation socket.\n");
		return -1;
	}
	genl_connect(inst->sock);

	inst->family_id = genl_ctrl_resolve(inst->sock, NL_CLASSIFIER_GENL_FAMILY);
	if (inst->family_id < 0) {
		printf("Unable to resolve family %s\n", NL_CLASSIFIER_GENL_FAMILY);
		goto init_failed;
	}

	inst->group_id = genl_ctrl_resolve_grp(inst->sock, NL_CLASSIFIER_GENL_FAMILY, NL_CLASSIFIER_GENL_GROUP);
	if (inst->group_id < 0) {
		printf("Unable to resolve mcast group %s\n", NL_CLASSIFIER_GENL_GROUP);
		goto init_failed;
	}

	ret = nl_socket_add_membership(inst->sock, inst->group_id);
	if (ret < 0) {
		printf("Unable to add membership\n");
		goto init_failed;
	}

	nl_socket_disable_seq_check(inst->sock);
	nl_socket_modify_cb(inst->sock, NL_CB_VALID, NL_CB_CUSTOM, nl_classifier_msg_recv, NULL);

	printf("nl classifier init successful\n");
	return 0;

init_failed:
	if (inst->sock) {
		nl_close(inst->sock);
		nl_socket_free(inst->sock);
		inst->sock = NULL;
	}
	return -1;
}