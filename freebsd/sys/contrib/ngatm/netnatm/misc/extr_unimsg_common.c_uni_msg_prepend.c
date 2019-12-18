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
struct uni_msg {size_t b_rptr; size_t b_wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ uni_msg_ensure (struct uni_msg*,size_t) ; 
 size_t uni_msg_leading (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_msg_len (struct uni_msg*) ; 

int
uni_msg_prepend(struct uni_msg *msg, size_t len)
{
	size_t need;

	if (uni_msg_leading(msg) >= len) {
		msg->b_rptr -= len;
		return (0);
	}
	need = len - uni_msg_leading(msg);
	if (uni_msg_ensure(msg, need))
		return (-1);
	memcpy(msg->b_rptr + need, msg->b_rptr, uni_msg_len(msg));
	msg->b_rptr += need - len;
	msg->b_wptr += need;
	return (0);
}