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
struct rsocket {int state; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  ctrl_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_CTRL_KEEPALIVE ; 
 int /*<<< orphan*/  RS_OP_CTRL ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int rs_connected ; 
 scalar_t__ rs_ctrl_avail (struct rsocket*) ; 
 int /*<<< orphan*/  rs_msg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_post_write (struct rsocket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 

__attribute__((used)) static void tcp_svc_send_keepalive(struct rsocket *rs)
{
	fastlock_acquire(&rs->cq_lock);
	if (rs_ctrl_avail(rs) && (rs->state & rs_connected)) {
		rs->ctrl_seqno++;
		rs_post_write(rs, NULL, 0, rs_msg_set(RS_OP_CTRL, RS_CTRL_KEEPALIVE),
			      0, (uintptr_t) NULL, (uintptr_t) NULL);
	}
	fastlock_release(&rs->cq_lock);
}