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
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_end_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_cur_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pf_req ; 

__attribute__((used)) static void pf_end_request(blk_status_t err)
{
	if (!pf_req)
		return;
	if (!blk_update_request(pf_req, err, blk_rq_cur_bytes(pf_req))) {
		__blk_mq_end_request(pf_req, err);
		pf_req = NULL;
	}
}