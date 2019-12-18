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
struct pcpu {int /*<<< orphan*/  pc_ipimask; int /*<<< orphan*/  pc_hwref; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ) ; 

void
db_show_mdpcpu(struct pcpu *pc)
{

	db_printf("PPC: hwref   = %#zx\n", pc->pc_hwref);
	db_printf("PPC: ipimask = %#x\n", pc->pc_ipimask);
}