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
typedef  enum blk_req_status { ____Placeholder_blk_req_status } blk_req_status ;

/* Variables and functions */
 int BLKIF_RSP_EOPNOTSUPP ; 
 int BLKIF_RSP_ERROR ; 
 int BLKIF_RSP_OKAY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int REQ_EOPNOTSUPP ; 
 int REQ_ERROR ; 
 int REQ_WAITING ; 

__attribute__((used)) static int blkif_get_final_status(enum blk_req_status s1,
				  enum blk_req_status s2)
{
	BUG_ON(s1 == REQ_WAITING);
	BUG_ON(s2 == REQ_WAITING);

	if (s1 == REQ_ERROR || s2 == REQ_ERROR)
		return BLKIF_RSP_ERROR;
	else if (s1 == REQ_EOPNOTSUPP || s2 == REQ_EOPNOTSUPP)
		return BLKIF_RSP_EOPNOTSUPP;
	return BLKIF_RSP_OKAY;
}