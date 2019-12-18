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
struct request {struct hd_struct* part; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_do_io_stat (struct request*) ; 
 int op_stat_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_add (struct hd_struct*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/  req_op (struct request*) ; 
 int /*<<< orphan*/ * sectors ; 

void blk_account_io_completion(struct request *req, unsigned int bytes)
{
	if (blk_do_io_stat(req)) {
		const int sgrp = op_stat_group(req_op(req));
		struct hd_struct *part;

		part_stat_lock();
		part = req->part;
		part_stat_add(part, sectors[sgrp], bytes >> 9);
		part_stat_unlock();
	}
}