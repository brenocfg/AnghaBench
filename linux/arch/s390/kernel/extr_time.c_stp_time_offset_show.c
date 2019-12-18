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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int vbits; scalar_t__ tto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__ stp_info ; 
 int /*<<< orphan*/  stp_online ; 

__attribute__((used)) static ssize_t stp_time_offset_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	if (!stp_online || !(stp_info.vbits & 0x0800))
		return -ENODATA;
	return sprintf(buf, "%i\n", (int) stp_info.tto);
}