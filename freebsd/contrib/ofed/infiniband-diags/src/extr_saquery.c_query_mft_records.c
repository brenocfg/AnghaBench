#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct sa_handle {int dummy; } ;
struct query_params {int dummy; } ;
struct query_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  mftr ;
typedef  int /*<<< orphan*/  ib_net64_t ;
struct TYPE_4__ {int lid; int position_block_num; } ;
typedef  TYPE_1__ ib_mft_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK ; 
 int /*<<< orphan*/  CHECK_AND_SET_VAL (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IB_MCAST_BLOCK_ID_MASK_HO ; 
 int /*<<< orphan*/  IB_SA_ATTR_MFTRECORD ; 
 int /*<<< orphan*/  LID ; 
 int /*<<< orphan*/  MFTR ; 
 int /*<<< orphan*/  POSITION ; 
 int cl_hton16 (int) ; 
 int /*<<< orphan*/  dump_one_mft_record ; 
 int get_and_dump_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,struct query_params*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_lid_and_ports (struct sa_handle*,char*,int*,int*,int*) ; 

__attribute__((used)) static int query_mft_records(const struct query_cmd *q, struct sa_handle * h,
			     struct query_params *p, int argc, char *argv[])
{
	ib_mft_record_t mftr;
	ib_net64_t comp_mask = 0;
	int lid = 0, block = -1, position = -1;
	uint16_t pos = 0;

	if (argc > 0)
		parse_lid_and_ports(h, argv[0], &lid, &position, &block);

	memset(&mftr, 0, sizeof(mftr));
	CHECK_AND_SET_VAL(lid, 16, 0, mftr.lid, MFTR, LID);
	CHECK_AND_SET_VAL(block, 16, -1, mftr.position_block_num, MFTR, BLOCK);
	mftr.position_block_num &= cl_hton16(IB_MCAST_BLOCK_ID_MASK_HO);
	CHECK_AND_SET_VAL(position, 8, -1, pos, MFTR, POSITION);
	mftr.position_block_num |= cl_hton16(pos << 12);

	return get_and_dump_any_records(h, IB_SA_ATTR_MFTRECORD, 0, comp_mask,
					&mftr, sizeof(mftr), dump_one_mft_record, p);
}