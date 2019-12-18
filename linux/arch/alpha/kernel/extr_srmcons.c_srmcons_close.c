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
struct tty_struct {int count; struct srmcons_private* driver_data; } ;
struct tty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; } ;
struct srmcons_private {int /*<<< orphan*/  timer; struct tty_port port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
srmcons_close(struct tty_struct *tty, struct file *filp)
{
	struct srmcons_private *srmconsp = tty->driver_data;
	struct tty_port *port = &srmconsp->port;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	if (tty->count == 1) {
		port->tty = NULL;
		del_timer(&srmconsp->timer);
	}

	spin_unlock_irqrestore(&port->lock, flags);
}