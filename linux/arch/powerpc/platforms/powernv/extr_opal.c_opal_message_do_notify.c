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
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,size_t,void*) ; 
 int /*<<< orphan*/ * opal_msg_notifier_head ; 

__attribute__((used)) static void opal_message_do_notify(uint32_t msg_type, void *msg)
{
	/* notify subscribers */
	atomic_notifier_call_chain(&opal_msg_notifier_head[msg_type],
					msg_type, msg);
}