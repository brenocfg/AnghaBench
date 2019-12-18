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
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mambo_callout ; 
 TYPE_1__ mambo_consdev ; 
 int /*<<< orphan*/  mambo_timeout ; 
 int /*<<< orphan*/  mambo_ttydevsw ; 
 int polltime ; 
 int /*<<< orphan*/  tp ; 
 int /*<<< orphan*/  tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_init_console (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
cn_drvinit(void *unused)
{

	if (mambo_consdev.cn_pri != CN_DEAD &&
	    mambo_consdev.cn_name[0] != '\0') {
		if (OF_finddevice("/mambo") == -1)
			return;

		tp = tty_alloc(&mambo_ttydevsw, NULL);
		tty_init_console(tp, 0);
		tty_makedev(tp, NULL, "%s", "mambocons");

		polltime = 1;

		callout_init(&mambo_callout, 1);
		callout_reset(&mambo_callout, polltime, mambo_timeout, NULL);
	}
}