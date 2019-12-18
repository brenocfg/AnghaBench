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
struct pcpu {int /*<<< orphan*/  pc_curpmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ) ; 

void
db_show_mdpcpu(struct pcpu *pc)
{

#if __ARM_ARCH >= 6
	db_printf("curpmap      = %p\n", pc->pc_curpmap);
#endif
}