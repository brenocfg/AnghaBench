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
struct ipmi_user {struct ipmi_smi* intf; } ;
struct ipmi_smi {int /*<<< orphan*/  cmd_rcvrs_mutex; int /*<<< orphan*/  cmd_rcvrs; } ;
struct cmd_rcvr {unsigned char cmd; unsigned char netfn; unsigned int chans; int /*<<< orphan*/  link; struct ipmi_user* user; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPMI_WATCH_MASK_CHECK_COMMANDS ; 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 int /*<<< orphan*/  is_cmd_rcvr_exclusive (struct ipmi_smi*,unsigned char,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct cmd_rcvr*) ; 
 struct cmd_rcvr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 
 int /*<<< orphan*/  smi_add_watch (struct ipmi_smi*,int /*<<< orphan*/ ) ; 

int ipmi_register_for_cmd(struct ipmi_user *user,
			  unsigned char netfn,
			  unsigned char cmd,
			  unsigned int  chans)
{
	struct ipmi_smi *intf = user->intf;
	struct cmd_rcvr *rcvr;
	int rv = 0, index;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	rcvr = kmalloc(sizeof(*rcvr), GFP_KERNEL);
	if (!rcvr) {
		rv = -ENOMEM;
		goto out_release;
	}
	rcvr->cmd = cmd;
	rcvr->netfn = netfn;
	rcvr->chans = chans;
	rcvr->user = user;

	mutex_lock(&intf->cmd_rcvrs_mutex);
	/* Make sure the command/netfn is not already registered. */
	if (!is_cmd_rcvr_exclusive(intf, netfn, cmd, chans)) {
		rv = -EBUSY;
		goto out_unlock;
	}

	smi_add_watch(intf, IPMI_WATCH_MASK_CHECK_COMMANDS);

	list_add_rcu(&rcvr->link, &intf->cmd_rcvrs);

out_unlock:
	mutex_unlock(&intf->cmd_rcvrs_mutex);
	if (rv)
		kfree(rcvr);
out_release:
	release_ipmi_user(user, index);

	return rv;
}