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
struct nullb_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum req_opf { ____Placeholder_req_opf } req_opf ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
#define  REQ_OP_WRITE 130 
#define  REQ_OP_ZONE_RESET 129 
#define  REQ_OP_ZONE_RESET_ALL 128 
 int /*<<< orphan*/  null_zone_reset (struct nullb_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_zone_write (struct nullb_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

blk_status_t null_handle_zoned(struct nullb_cmd *cmd, enum req_opf op,
			       sector_t sector, sector_t nr_sectors)
{
	switch (op) {
	case REQ_OP_WRITE:
		return null_zone_write(cmd, sector, nr_sectors);
	case REQ_OP_ZONE_RESET:
	case REQ_OP_ZONE_RESET_ALL:
		return null_zone_reset(cmd, sector);
	default:
		return BLK_STS_OK;
	}
}