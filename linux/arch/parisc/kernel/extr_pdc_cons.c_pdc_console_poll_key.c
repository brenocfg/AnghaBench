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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdc_console_lock ; 
 int pdc_iodc_getc () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_console_poll_key(struct console *co)
{
	int c;
	unsigned long flags;

	spin_lock_irqsave(&pdc_console_lock, flags);
	c = pdc_iodc_getc();
	spin_unlock_irqrestore(&pdc_console_lock, flags);

	return c;
}