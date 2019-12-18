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
 int /*<<< orphan*/ * fd_request ; 

__attribute__((used)) static void fd_end_request_cur(blk_status_t err)
{
	if (!blk_update_request(fd_request, err,
				blk_rq_cur_bytes(fd_request))) {
		__blk_mq_end_request(fd_request, err);
		fd_request = NULL;
	}
}