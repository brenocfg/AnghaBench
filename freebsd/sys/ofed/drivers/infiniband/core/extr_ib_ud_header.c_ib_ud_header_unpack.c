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
struct TYPE_2__ {scalar_t__ link_version; int link_next_header; int ip_version; int next_header; int opcode; scalar_t__ transport_header_version; } ;
struct ib_ud_header {int grh_present; int immediate_present; int /*<<< orphan*/  immediate_data; TYPE_1__ deth; TYPE_1__ bth; TYPE_1__ lrh; TYPE_1__ grh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int IB_BTH_BYTES ; 
 int IB_DETH_BYTES ; 
 int /*<<< orphan*/  IB_GRH_BYTES ; 
#define  IB_LNH_IBA_GLOBAL 131 
#define  IB_LNH_IBA_LOCAL 130 
 int IB_LRH_BYTES ; 
#define  IB_OPCODE_UD_SEND_ONLY 129 
#define  IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE 128 
 int /*<<< orphan*/  bth_table ; 
 int /*<<< orphan*/  deth_table ; 
 int /*<<< orphan*/  grh_table ; 
 int /*<<< orphan*/  ib_unpack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  lrh_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

int ib_ud_header_unpack(void                *buf,
			struct ib_ud_header *header)
{
	ib_unpack(lrh_table, ARRAY_SIZE(lrh_table),
		  buf, &header->lrh);
	buf = (char *)buf + IB_LRH_BYTES;

	if (header->lrh.link_version != 0) {
		pr_warn("Invalid LRH.link_version %d\n",
			header->lrh.link_version);
		return -EINVAL;
	}

	switch (header->lrh.link_next_header) {
	case IB_LNH_IBA_LOCAL:
		header->grh_present = 0;
		break;

	case IB_LNH_IBA_GLOBAL:
		header->grh_present = 1;
		ib_unpack(grh_table, ARRAY_SIZE(grh_table),
			  buf, &header->grh);
		buf = (char *)buf + IB_GRH_BYTES;

		if (header->grh.ip_version != 6) {
			pr_warn("Invalid GRH.ip_version %d\n",
				header->grh.ip_version);
			return -EINVAL;
		}
		if (header->grh.next_header != 0x1b) {
			pr_warn("Invalid GRH.next_header 0x%02x\n",
				header->grh.next_header);
			return -EINVAL;
		}
		break;

	default:
		pr_warn("Invalid LRH.link_next_header %d\n",
			header->lrh.link_next_header);
		return -EINVAL;
	}

	ib_unpack(bth_table, ARRAY_SIZE(bth_table),
		  buf, &header->bth);
	buf = (char *)buf + IB_BTH_BYTES;

	switch (header->bth.opcode) {
	case IB_OPCODE_UD_SEND_ONLY:
		header->immediate_present = 0;
		break;
	case IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE:
		header->immediate_present = 1;
		break;
	default:
		pr_warn("Invalid BTH.opcode 0x%02x\n", header->bth.opcode);
		return -EINVAL;
	}

	if (header->bth.transport_header_version != 0) {
		pr_warn("Invalid BTH.transport_header_version %d\n",
			header->bth.transport_header_version);
		return -EINVAL;
	}

	ib_unpack(deth_table, ARRAY_SIZE(deth_table),
		  buf, &header->deth);
	buf = (char *)buf + IB_DETH_BYTES;

	if (header->immediate_present)
		memcpy(&header->immediate_data, buf, sizeof header->immediate_data);

	return 0;
}