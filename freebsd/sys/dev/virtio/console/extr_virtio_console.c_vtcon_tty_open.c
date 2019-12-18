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
struct vtcon_port {int vtcport_flags; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VIRTIO_CONSOLE_PORT_OPEN ; 
 int VTCON_PORT_FLAG_GONE ; 
 struct vtcon_port* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  vtcon_port_submit_event (struct vtcon_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vtcon_tty_open(struct tty *tp)
{
	struct vtcon_port *port;

	port = tty_softc(tp);

	if (port->vtcport_flags & VTCON_PORT_FLAG_GONE)
		return (ENXIO);

	vtcon_port_submit_event(port, VIRTIO_CONSOLE_PORT_OPEN, 1);

	return (0);
}