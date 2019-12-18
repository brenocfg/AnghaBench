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
struct request {int dummy; } ;
struct floppy_state {struct request* cur_req; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_cur_bytes (struct request*) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  swim3_dbg (char*,int /*<<< orphan*/ ,unsigned int,struct request*) ; 

__attribute__((used)) static bool swim3_end_request(struct floppy_state *fs, blk_status_t err, unsigned int nr_bytes)
{
	struct request *req = fs->cur_req;

	swim3_dbg("  end request, err=%d nr_bytes=%d, cur_req=%p\n",
		  err, nr_bytes, req);

	if (err)
		nr_bytes = blk_rq_cur_bytes(req);
	if (blk_update_request(req, err, nr_bytes))
		return true;
	__blk_mq_end_request(req, err);
	fs->cur_req = NULL;
	return false;
}