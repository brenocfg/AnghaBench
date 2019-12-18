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
struct notifier_block {int dummy; } ;
typedef  enum opal_msg_type { ____Placeholder_opal_msg_type } opal_msg_type ;

/* Variables and functions */
 int atomic_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/ * opal_msg_notifier_head ; 

int opal_message_notifier_unregister(enum opal_msg_type msg_type,
				     struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(
			&opal_msg_notifier_head[msg_type], nb);
}