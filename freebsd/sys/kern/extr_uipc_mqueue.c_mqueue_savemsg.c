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
struct mqueue_msg {int msg_size; char msg_prio; } ;

/* Variables and functions */
 int copyout (char*,...) ; 

__attribute__((used)) static int
mqueue_savemsg(struct mqueue_msg *msg, char *msg_ptr, int *msg_prio)
{
	int error;

	error = copyout(((char *)msg) + sizeof(*msg), msg_ptr,
		msg->msg_size);
	if (error == 0 && msg_prio != NULL)
		error = copyout(&msg->msg_prio, msg_prio, sizeof(int));
	return (error);
}