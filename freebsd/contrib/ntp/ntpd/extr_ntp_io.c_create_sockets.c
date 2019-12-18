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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  activefds ; 
 int /*<<< orphan*/  create_wildcards (int /*<<< orphan*/ ) ; 
 scalar_t__ maxactivefd ; 
 int ninterfaces ; 
 int /*<<< orphan*/  set_reuseaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
create_sockets(
	u_short port
	)
{
#ifndef HAVE_IO_COMPLETION_PORT
	/*
	 * I/O Completion Ports don't care about the select and FD_SET
	 */
	maxactivefd = 0;
	FD_ZERO(&activefds);
#endif

	DPRINTF(2, ("create_sockets(%d)\n", port));

	create_wildcards(port);

	update_interfaces(port, NULL, NULL);

	/*
	 * Now that we have opened all the sockets, turn off the reuse
	 * flag for security.
	 */
	set_reuseaddr(0);

	DPRINTF(2, ("create_sockets: Total interfaces = %d\n", ninterfaces));

	return ninterfaces;
}