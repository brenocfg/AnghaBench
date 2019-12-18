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
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
#define  BRIDGE_WIDGET_PART_NUM 129 
 scalar_t__ RAW_NODE_SWIN_BASE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WIDGET_ID ; 
#define  XBRIDGE_WIDGET_PART_NUM 128 
 int XWIDGET_PART_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_platform_create (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int probe_one_port(nasid_t nasid, int widget, int masterwid)
{
	widgetreg_t		widget_id;
	xwidget_part_num_t	partnum;

	widget_id = *(volatile widgetreg_t *)
		(RAW_NODE_SWIN_BASE(nasid, widget) + WIDGET_ID);
	partnum = XWIDGET_PART_NUM(widget_id);

	switch (partnum) {
	case BRIDGE_WIDGET_PART_NUM:
	case XBRIDGE_WIDGET_PART_NUM:
		bridge_platform_create(nasid, widget, masterwid);
		break;
	default:
		break;
	}

	return 0;
}