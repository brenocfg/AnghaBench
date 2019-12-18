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
struct rsocket {int opts; int rbuf_bytes_avail; int rbuf_size; int state; scalar_t__ rseq_comp; scalar_t__ rseq_no; } ;

/* Variables and functions */
 int RS_OPT_MSG_SEND ; 
 scalar_t__ rs_2ctrl_avail (struct rsocket*) ; 
 int rs_connected ; 
 scalar_t__ rs_ctrl_avail (struct rsocket*) ; 

__attribute__((used)) static int rs_give_credits(struct rsocket *rs)
{
	if (!(rs->opts & RS_OPT_MSG_SEND)) {
		return ((rs->rbuf_bytes_avail >= (rs->rbuf_size >> 1)) ||
			((short) ((short) rs->rseq_no - (short) rs->rseq_comp) >= 0)) &&
		       rs_ctrl_avail(rs) && (rs->state & rs_connected);
	} else {
		return ((rs->rbuf_bytes_avail >= (rs->rbuf_size >> 1)) ||
			((short) ((short) rs->rseq_no - (short) rs->rseq_comp) >= 0)) &&
		       rs_2ctrl_avail(rs) && (rs->state & rs_connected);
	}
}