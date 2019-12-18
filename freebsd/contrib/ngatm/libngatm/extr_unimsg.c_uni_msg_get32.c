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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int b_rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

u_int
uni_msg_get32(struct uni_msg *msg)
{
	uint32_t w;

	bcopy(msg->b_rptr, &w, 4);
	msg->b_rptr += 4;
	return (ntohl(w));
}