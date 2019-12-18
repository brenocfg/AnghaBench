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

/* Variables and functions */
 int /*<<< orphan*/  BLOCKIO () ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ HAVE_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int /*<<< orphan*/  SAVECONFIGQUIT ; 
 int /*<<< orphan*/  UNBLOCKIO () ; 
 int /*<<< orphan*/  create_sockets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_async_notifications () ; 
 int /*<<< orphan*/  maxactivefd ; 

void
io_open_sockets(void)
{
	static int already_opened;

	if (already_opened || HAVE_OPT( SAVECONFIGQUIT ))
		return;

	already_opened = 1;

	/*
	 * Create the sockets
	 */
	BLOCKIO();
	create_sockets(NTP_PORT);
	UNBLOCKIO();

	init_async_notifications();

	DPRINTF(3, ("io_open_sockets: maxactivefd %d\n", maxactivefd));
}