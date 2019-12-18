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
struct notifier_block {int dummy; } ;
struct charlcd {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  SYS_DOWN 130 
#define  SYS_HALT 129 
#define  SYS_POWER_OFF 128 
 int /*<<< orphan*/  charlcd_puts (struct charlcd*,char*) ; 
 struct charlcd* the_charlcd ; 

__attribute__((used)) static int panel_notify_sys(struct notifier_block *this, unsigned long code,
			    void *unused)
{
	struct charlcd *lcd = the_charlcd;

	switch (code) {
	case SYS_DOWN:
		charlcd_puts(lcd,
			     "\x0cReloading\nSystem...\x1b[Lc\x1b[Lb\x1b[L+");
		break;
	case SYS_HALT:
		charlcd_puts(lcd, "\x0cSystem Halted.\x1b[Lc\x1b[Lb\x1b[L+");
		break;
	case SYS_POWER_OFF:
		charlcd_puts(lcd, "\x0cPower off.\x1b[Lc\x1b[Lb\x1b[L+");
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}