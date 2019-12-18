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
struct si_sm_io {int dummy; } ;
struct si_sm_data {int BT_CAP_req2rsp; int /*<<< orphan*/  BT_CAP_retries; void* complete; void* state; scalar_t__ seq; struct si_sm_io* io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_NORMAL_RETRY_LIMIT ; 
 int BT_NORMAL_TIMEOUT ; 
 void* BT_STATE_IDLE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  memset (struct si_sm_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int bt_init_data(struct si_sm_data *bt, struct si_sm_io *io)
{
	memset(bt, 0, sizeof(struct si_sm_data));
	if (bt->io != io) {
		/* external: one-time only things */
		bt->io = io;
		bt->seq = 0;
	}
	bt->state = BT_STATE_IDLE;	/* start here */
	bt->complete = BT_STATE_IDLE;	/* end here */
	bt->BT_CAP_req2rsp = BT_NORMAL_TIMEOUT * USEC_PER_SEC;
	bt->BT_CAP_retries = BT_NORMAL_RETRY_LIMIT;
	return 3; /* We claim 3 bytes of space; ought to check SPMI table */
}