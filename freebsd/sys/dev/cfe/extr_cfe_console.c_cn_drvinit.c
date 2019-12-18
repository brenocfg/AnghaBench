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
struct tty {int dummy; } ;
struct TYPE_2__ {scalar_t__ cn_pri; char* cn_name; } ;

/* Variables and functions */
 scalar_t__ CN_DEAD ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cfe_consdev ; 
 int /*<<< orphan*/  cfe_timer ; 
 int /*<<< orphan*/  cfe_ttydevsw ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_getlock (struct tty*) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
cn_drvinit(void *unused)
{
	struct tty *tp;

	if (cfe_consdev.cn_pri != CN_DEAD &&
	    cfe_consdev.cn_name[0] != '\0') {
		tp = tty_alloc(&cfe_ttydevsw, NULL);
		callout_init_mtx(&cfe_timer, tty_getlock(tp), 0);
		tty_makedev(tp, NULL, "cfecons");
	}
}