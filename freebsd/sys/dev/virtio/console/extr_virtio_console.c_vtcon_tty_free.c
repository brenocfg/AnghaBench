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
struct vtcon_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vtcon_pending_free ; 
 int /*<<< orphan*/  vtcon_port_destroy (struct vtcon_port*) ; 

__attribute__((used)) static void
vtcon_tty_free(void *xport)
{
	struct vtcon_port *port;

	port = xport;

	vtcon_port_destroy(port);
	atomic_subtract_int(&vtcon_pending_free, 1);
}