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
struct uni_msg {scalar_t__ b_wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

u_int
uni_msg_trail32(const struct uni_msg *msg, int i)
{
	u_int w;

	bcopy(msg->b_wptr + 4 * i, &w, 4);
	return (ntohl(w));
}