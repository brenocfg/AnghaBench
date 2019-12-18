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
struct mqueue_msg {size_t msg_size; int msg_prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MQUEUEDATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyin (char const*,char*,size_t) ; 
 int /*<<< orphan*/  free (struct mqueue_msg*,int /*<<< orphan*/ ) ; 
 struct mqueue_msg* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mqueue_msg *
mqueue_loadmsg(const char *msg_ptr, size_t msg_size, int msg_prio)
{
	struct mqueue_msg *msg;
	size_t len;
	int error;

	len = sizeof(struct mqueue_msg) + msg_size;
	msg = malloc(len, M_MQUEUEDATA, M_WAITOK);
	error = copyin(msg_ptr, ((char *)msg) + sizeof(struct mqueue_msg),
	    msg_size);
	if (error) {
		free(msg, M_MQUEUEDATA);
		msg = NULL;
	} else {
		msg->msg_size = msg_size;
		msg->msg_prio = msg_prio;
	}
	return (msg);
}