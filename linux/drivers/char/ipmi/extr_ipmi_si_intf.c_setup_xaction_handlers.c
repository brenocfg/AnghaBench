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
struct smi_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_dell_poweredge_bt_xaction_handler (struct smi_info*) ; 

__attribute__((used)) static void setup_xaction_handlers(struct smi_info *smi_info)
{
	setup_dell_poweredge_bt_xaction_handler(smi_info);
}