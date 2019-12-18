#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_2__ {struct task_struct* task; } ;
struct drbd_connection {TYPE_1__ ack_receiver; } ;

/* Variables and functions */
 scalar_t__ RUNNING ; 
 int /*<<< orphan*/  SIGXCPU ; 
 scalar_t__ get_t_state (TYPE_1__*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,struct task_struct*,int) ; 

__attribute__((used)) static inline void wake_ack_receiver(struct drbd_connection *connection)
{
	struct task_struct *task = connection->ack_receiver.task;
	if (task && get_t_state(&connection->ack_receiver) == RUNNING)
		send_sig(SIGXCPU, task, 1);
}