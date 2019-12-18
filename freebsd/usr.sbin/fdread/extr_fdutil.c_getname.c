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
typedef  enum fd_drivetype { ____Placeholder_fd_drivetype } fd_drivetype ;

/* Variables and functions */
#define  FDT_12M 132 
#define  FDT_144M 131 
#define  FDT_288M 130 
#define  FDT_360K 129 
#define  FDT_720K 128 

void
getname(enum fd_drivetype t, const char **name, const char **descr)
{

	switch (t) {
	default:
		*name = "unknown";
		*descr = "unknown drive type";
		break;

	case FDT_360K:
		*name = "360K";
		*descr = "5.25\" double-density";
		break;

	case FDT_12M:
		*name = "1.2M";
		*descr = "5.25\" high-density";
		break;

	case FDT_720K:
		*name = "720K";
		*descr = "3.5\" double-density";
		break;

	case FDT_144M:
		*name = "1.44M";
		*descr = "3.5\" high-density";
		break;

	case FDT_288M:
		*name = "2.88M";
		*descr = "3.5\" extra-density";
		break;
	}
}