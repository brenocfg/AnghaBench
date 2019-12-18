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
struct request {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 int queue_max_discard_segments (int /*<<< orphan*/ ) ; 
 scalar_t__ req_op (struct request*) ; 

__attribute__((used)) static inline bool blk_discard_mergable(struct request *req)
{
	if (req_op(req) == REQ_OP_DISCARD &&
	    queue_max_discard_segments(req->q) > 1)
		return true;
	return false;
}