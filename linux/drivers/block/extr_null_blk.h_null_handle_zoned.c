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
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 

__attribute__((used)) static inline blk_status_t null_handle_zoned(struct nullb_cmd *cmd,
					     enum req_opf op, sector_t sector,
					     sector_t nr_sectors)
{
	return BLK_STS_NOTSUPP;
}