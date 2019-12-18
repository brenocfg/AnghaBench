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
typedef  int xwidget_part_num_t ;
typedef  int /*<<< orphan*/  widgetreg_t ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  nasid_t ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
#define  BRIDGE_WIDGET_PART_NUM 130 
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_LLP_CSR ; 
 int volatile IIO_LLP_CSR_IS_UP ; 
 scalar_t__ RAW_NODE_SWIN_BASE (int /*<<< orphan*/ ,int) ; 
 int REMOTE_HUB_L (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WIDGET_ID ; 
#define  XBOW_WIDGET_PART_NUM 129 
 int XWIDGET_PART_NUM (int /*<<< orphan*/ ) ; 
#define  XXBOW_WIDGET_PART_NUM 128 
 int /*<<< orphan*/  bridge_platform_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xbow_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtalk_probe_node(cnodeid_t nid)
{
	volatile u64		hubreg;
	nasid_t			nasid;
	xwidget_part_num_t	partnum;
	widgetreg_t		widget_id;

	nasid = COMPACT_TO_NASID_NODEID(nid);
	hubreg = REMOTE_HUB_L(nasid, IIO_LLP_CSR);

	/* check whether the link is up */
	if (!(hubreg & IIO_LLP_CSR_IS_UP))
		return;

	widget_id = *(volatile widgetreg_t *)
		       (RAW_NODE_SWIN_BASE(nasid, 0x0) + WIDGET_ID);
	partnum = XWIDGET_PART_NUM(widget_id);

	switch (partnum) {
	case BRIDGE_WIDGET_PART_NUM:
		bridge_platform_create(nasid, 0x8, 0xa);
		break;
	case XBOW_WIDGET_PART_NUM:
	case XXBOW_WIDGET_PART_NUM:
		pr_info("xtalk:n%d/0 xbow widget\n", nasid);
		xbow_probe(nasid);
		break;
	default:
		pr_info("xtalk:n%d/0 unknown widget (0x%x)\n", nasid, partnum);
		break;
	}
}