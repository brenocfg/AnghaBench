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
#define  BLKIF_RSP_EOPNOTSUPP 130 
#define  BLKIF_RSP_ERROR 129 
#define  BLKIF_RSP_OKAY 128 
 int REQ_DONE ; 
 int REQ_EOPNOTSUPP ; 
 int REQ_ERROR ; 

__attribute__((used)) static enum blk_req_status blkif_rsp_to_req_status(int rsp)
{
	switch (rsp)
	{
	case BLKIF_RSP_OKAY:
		return REQ_DONE;
	case BLKIF_RSP_EOPNOTSUPP:
		return REQ_EOPNOTSUPP;
	case BLKIF_RSP_ERROR:
		/* Fallthrough. */
	default:
		return REQ_ERROR;
	}
}