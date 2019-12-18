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
struct rsocket {scalar_t__ sqe_avail; scalar_t__ sq_size; int state; scalar_t__ ctrl_seqno; scalar_t__ ctrl_max_seqno; } ;

/* Variables and functions */
 int rs_connected ; 

__attribute__((used)) static int rs_conn_all_sends_done(struct rsocket *rs)
{
	return ((((int) rs->ctrl_max_seqno) - ((int) rs->ctrl_seqno)) +
		rs->sqe_avail == rs->sq_size) ||
	       !(rs->state & rs_connected);
}