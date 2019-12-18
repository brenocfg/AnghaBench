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
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int b_wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int uni_msg_ensure (struct uni_msg*,int) ; 

int
uni_msg_append32(struct uni_msg *msg, u_int u)
{
	if (uni_msg_ensure(msg, 4) == -1)
		return (-1);
	u = htonl(u);
	bcopy(&u, msg->b_wptr, 4);
	msg->b_wptr += 4;
	return (0);
}