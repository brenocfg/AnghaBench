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
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_completion_port_remove_interface (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
delete_interface(
	endpt *ep
	)
{
#    ifdef HAVE_IO_COMPLETION_PORT
	io_completion_port_remove_interface(ep);
#    endif
	free(ep);
}