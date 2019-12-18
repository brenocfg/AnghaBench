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
struct ssif_info {int /*<<< orphan*/  ssif_state; int /*<<< orphan*/ * curr_msg; } ;
struct ipmi_smi_msg {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSIF_NORMAL ; 
 int /*<<< orphan*/  ipmi_free_smi_msg (struct ipmi_smi_msg*) ; 
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 scalar_t__ start_send (struct ssif_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_start_send(struct ssif_info *ssif_info, unsigned long *flags,
			     struct ipmi_smi_msg *msg)
{
	if (start_send(ssif_info, msg->data, msg->data_size) != 0) {
		unsigned long oflags;

		flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
		ssif_info->curr_msg = NULL;
		ssif_info->ssif_state = SSIF_NORMAL;
		ipmi_ssif_unlock_cond(ssif_info, flags);
		ipmi_free_smi_msg(msg);
	}
}