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
struct TYPE_2__ {scalar_t__ cn_pri; char* cn_name; } ;

/* Variables and functions */
 scalar_t__ CN_DEAD ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int polltime ; 
 int /*<<< orphan*/  riscv_callout ; 
 TYPE_1__ riscv_consdev ; 
 int /*<<< orphan*/  riscv_timeout ; 
 int /*<<< orphan*/  riscv_ttydevsw ; 
 int /*<<< orphan*/  tp ; 
 int /*<<< orphan*/  tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_init_console (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
cn_drvinit(void *unused)
{

	if (riscv_consdev.cn_pri != CN_DEAD &&
	    riscv_consdev.cn_name[0] != '\0') {
		tp = tty_alloc(&riscv_ttydevsw, NULL);
		tty_init_console(tp, 0);
		tty_makedev(tp, NULL, "%s", "rcons");

		polltime = 1;

		callout_init(&riscv_callout, 1);
		callout_reset(&riscv_callout, polltime, riscv_timeout, NULL);
	}
}