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
struct unl {int /*<<< orphan*/  family; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  NL_AUTO_PID ; 
 int /*<<< orphan*/  NL_AUTO_SEQ ; 
 int /*<<< orphan*/  genl_family_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_put (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct nl_msg* nlmsg_alloc () ; 

struct nl_msg *unl_genl_msg(struct unl *unl, int cmd, bool dump)
{
	struct nl_msg *msg;
	int flags = 0;

	msg = nlmsg_alloc();
	if (!msg)
		goto out;

	if (dump)
		flags |= NLM_F_DUMP;

	genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ,
		    genl_family_get_id(unl->family), 0, flags, cmd, 0);

out:
	return msg;
}