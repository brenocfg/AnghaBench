#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 scalar_t__ ATAPI_MISC ; 
 scalar_t__ atapi_cmd_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ op_is_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_op (struct request*) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static int atapi_drain_needed(struct request *rq)
{
	if (likely(!blk_rq_is_passthrough(rq)))
		return 0;

	if (!blk_rq_bytes(rq) || op_is_write(req_op(rq)))
		return 0;

	return atapi_cmd_type(scsi_req(rq)->cmd[0]) == ATAPI_MISC;
}