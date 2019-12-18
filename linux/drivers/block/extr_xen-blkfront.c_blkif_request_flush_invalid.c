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
struct request {int cmd_flags; } ;
struct blkfront_info {int /*<<< orphan*/  feature_fua; int /*<<< orphan*/  feature_flush; } ;

/* Variables and functions */
 int REQ_FUA ; 
 scalar_t__ REQ_OP_FLUSH ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ req_op (struct request*) ; 

__attribute__((used)) static inline bool blkif_request_flush_invalid(struct request *req,
					       struct blkfront_info *info)
{
	return (blk_rq_is_passthrough(req) ||
		((req_op(req) == REQ_OP_FLUSH) &&
		 !info->feature_flush) ||
		((req->cmd_flags & REQ_FUA) &&
		 !info->feature_fua));
}