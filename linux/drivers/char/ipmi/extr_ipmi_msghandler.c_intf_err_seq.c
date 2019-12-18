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
struct seq_table {unsigned long seqid; struct ipmi_recv_msg* recv_msg; scalar_t__ inuse; } ;
struct ipmi_smi {int /*<<< orphan*/  seq_lock; struct seq_table* seq_table; } ;
struct ipmi_recv_msg {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GET_SEQ_FROM_MSGID (long,unsigned char,unsigned long) ; 
 int /*<<< orphan*/  IPMI_WATCH_MASK_CHECK_MESSAGES ; 
 int /*<<< orphan*/  deliver_err_response (struct ipmi_smi*,struct ipmi_recv_msg*,unsigned int) ; 
 int /*<<< orphan*/  smi_remove_watch (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int intf_err_seq(struct ipmi_smi *intf,
			long         msgid,
			unsigned int err)
{
	int                  rv = -ENODEV;
	unsigned long        flags;
	unsigned char        seq;
	unsigned long        seqid;
	struct ipmi_recv_msg *msg = NULL;


	GET_SEQ_FROM_MSGID(msgid, seq, seqid);

	spin_lock_irqsave(&intf->seq_lock, flags);
	/*
	 * We do this verification because the user can be deleted
	 * while a message is outstanding.
	 */
	if ((intf->seq_table[seq].inuse)
				&& (intf->seq_table[seq].seqid == seqid)) {
		struct seq_table *ent = &intf->seq_table[seq];

		ent->inuse = 0;
		smi_remove_watch(intf, IPMI_WATCH_MASK_CHECK_MESSAGES);
		msg = ent->recv_msg;
		rv = 0;
	}
	spin_unlock_irqrestore(&intf->seq_lock, flags);

	if (msg)
		deliver_err_response(intf, msg, err);

	return rv;
}