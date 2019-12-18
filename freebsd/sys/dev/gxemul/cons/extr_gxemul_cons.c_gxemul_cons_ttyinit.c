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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  gxemul_cons_callout ; 
 int /*<<< orphan*/  gxemul_cons_polltime ; 
 int /*<<< orphan*/  gxemul_cons_timeout ; 
 int /*<<< orphan*/  gxemul_cons_ttydevsw ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_init_console (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
gxemul_cons_ttyinit(void *unused)
{
	struct tty *tp;

	tp = tty_alloc(&gxemul_cons_ttydevsw, NULL);
	tty_init_console(tp, 0);
	tty_makedev(tp, NULL, "%s", "ttyu0");
	callout_init(&gxemul_cons_callout, 1);
	callout_reset(&gxemul_cons_callout, gxemul_cons_polltime,
	    gxemul_cons_timeout, tp);

}