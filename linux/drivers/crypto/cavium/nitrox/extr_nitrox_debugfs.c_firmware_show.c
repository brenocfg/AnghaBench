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
struct seq_file {struct nitrox_device* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fw_name; } ;
struct nitrox_device {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int firmware_show(struct seq_file *s, void *v)
{
	struct nitrox_device *ndev = s->private;

	seq_printf(s, "Version: %s\n", ndev->hw.fw_name[0]);
	seq_printf(s, "Version: %s\n", ndev->hw.fw_name[1]);
	return 0;
}