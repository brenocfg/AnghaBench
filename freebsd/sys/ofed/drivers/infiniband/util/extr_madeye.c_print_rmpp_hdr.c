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
struct ib_rmpp_hdr {int rmpp_type; int /*<<< orphan*/  paylen_newwin; int /*<<< orphan*/  seg_num; int /*<<< orphan*/  rmpp_status; int /*<<< orphan*/  rmpp_version; } ;

/* Variables and functions */
#define  IB_MGMT_RMPP_TYPE_ACK 129 
#define  IB_MGMT_RMPP_TYPE_DATA 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rmpp_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rmpp_type (int) ; 
 int /*<<< orphan*/  ib_get_rmpp_flags (struct ib_rmpp_hdr*) ; 
 int /*<<< orphan*/  ib_get_rmpp_resptime (struct ib_rmpp_hdr*) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

__attribute__((used)) static void print_rmpp_hdr(struct ib_rmpp_hdr *rmpp_hdr)
{
	printk("RMPP version...0x%01x\n", rmpp_hdr->rmpp_version);
	printk("RMPP type......0x%01x (%s)\n", rmpp_hdr->rmpp_type,
	       get_rmpp_type(rmpp_hdr->rmpp_type));
	printk("RMPP RRespTime.0x%01x\n", ib_get_rmpp_resptime(rmpp_hdr));
	printk("RMPP flags.....0x%01x (%s)\n", ib_get_rmpp_flags(rmpp_hdr),
	       get_rmpp_flags(ib_get_rmpp_flags(rmpp_hdr)));
	printk("RMPP status....0x%01x\n", rmpp_hdr->rmpp_status);
	printk("Seg number.....0x%04x\n", be32_to_cpu(rmpp_hdr->seg_num));
	switch (rmpp_hdr->rmpp_type) {
	case IB_MGMT_RMPP_TYPE_DATA:
		printk("Payload len....0x%04x\n",
		       be32_to_cpu(rmpp_hdr->paylen_newwin));
		break;
	case IB_MGMT_RMPP_TYPE_ACK:
		printk("New window.....0x%04x\n",
		       be32_to_cpu(rmpp_hdr->paylen_newwin));
		break;
	default:
		printk("Data 2.........0x%04x\n",
		       be32_to_cpu(rmpp_hdr->paylen_newwin));
		break;
	}
}