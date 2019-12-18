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
struct TYPE_2__ {size_t si_type; size_t addr_space; int /*<<< orphan*/  slave_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  regshift; int /*<<< orphan*/  regsize; int /*<<< orphan*/  regspacing; int /*<<< orphan*/  addr_data; } ;
struct smi_info {TYPE_1__ io; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** addr_space_to_str ; 
 struct smi_info* dev_get_drvdata (struct device*) ; 
 char** si_to_str ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t params_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct smi_info *smi_info = dev_get_drvdata(dev);

	return snprintf(buf, 200,
			"%s,%s,0x%lx,rsp=%d,rsi=%d,rsh=%d,irq=%d,ipmb=%d\n",
			si_to_str[smi_info->io.si_type],
			addr_space_to_str[smi_info->io.addr_space],
			smi_info->io.addr_data,
			smi_info->io.regspacing,
			smi_info->io.regsize,
			smi_info->io.regshift,
			smi_info->io.irq,
			smi_info->io.slave_addr);
}