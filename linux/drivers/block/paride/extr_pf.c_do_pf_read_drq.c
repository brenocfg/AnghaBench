#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 scalar_t__ PF_MAX_RETRIES ; 
 int /*<<< orphan*/  STAT_BUSY ; 
 int STAT_DRQ ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  do_pf_read_start ; 
 int /*<<< orphan*/  next_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_buf ; 
 TYPE_1__* pf_current ; 
 scalar_t__ pf_next_buf () ; 
 int /*<<< orphan*/  pf_req_sense (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pf_retries ; 
 int pf_wait (TYPE_1__*,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_do_claimed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_pf_read_drq(void)
{
	while (1) {
		if (pf_wait(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "read block", "completion") & STAT_ERR) {
			pi_disconnect(pf_current->pi);
			if (pf_retries < PF_MAX_RETRIES) {
				pf_req_sense(pf_current, 0);
				pf_retries++;
				pi_do_claimed(pf_current->pi, do_pf_read_start);
				return;
			}
			next_request(BLK_STS_IOERR);
			return;
		}
		pi_read_block(pf_current->pi, pf_buf, 512);
		if (pf_next_buf())
			break;
	}
	pi_disconnect(pf_current->pi);
	next_request(0);
}