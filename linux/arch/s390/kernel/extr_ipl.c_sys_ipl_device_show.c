#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int devno; } ;
struct TYPE_5__ {int ssid; int devno; } ;
struct TYPE_8__ {TYPE_2__ fcp; TYPE_1__ ccw; } ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
#define  IPL_TYPE_CCW 130 
#define  IPL_TYPE_FCP 129 
#define  IPL_TYPE_FCP_DUMP 128 
 TYPE_4__ ipl_block ; 
 TYPE_3__ ipl_info ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t sys_ipl_device_show(struct kobject *kobj,
				   struct kobj_attribute *attr, char *page)
{
	switch (ipl_info.type) {
	case IPL_TYPE_CCW:
		return sprintf(page, "0.%x.%04x\n", ipl_block.ccw.ssid,
			       ipl_block.ccw.devno);
	case IPL_TYPE_FCP:
	case IPL_TYPE_FCP_DUMP:
		return sprintf(page, "0.0.%04x\n", ipl_block.fcp.devno);
	default:
		return 0;
	}
}