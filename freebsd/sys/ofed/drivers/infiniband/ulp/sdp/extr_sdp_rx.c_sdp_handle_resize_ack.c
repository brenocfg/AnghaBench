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
typedef  scalar_t__ u32 ;
struct sdp_sock {scalar_t__ xmit_size_goal; } ;
struct sdp_chrecvbuf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_handle_resize_ack(struct sdp_sock *ssk, struct sdp_chrecvbuf *buf)
{
	u32 new_size = ntohl(buf->size);

	if (new_size > ssk->xmit_size_goal)
		ssk->xmit_size_goal = new_size;
}