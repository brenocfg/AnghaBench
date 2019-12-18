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
struct TYPE_2__ {scalar_t__ runtime_auto; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* ctrl_auto ; 
 char* ctrl_on ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t control_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	return sprintf(buf, "%s\n",
				dev->power.runtime_auto ? ctrl_auto : ctrl_on);
}