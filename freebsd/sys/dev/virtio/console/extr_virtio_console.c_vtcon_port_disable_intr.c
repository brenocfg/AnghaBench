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
struct vtcon_port {int /*<<< orphan*/ * vtcport_outvq; int /*<<< orphan*/ * vtcport_invq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_disable_intr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtcon_port_disable_intr(struct vtcon_port *port)
{

	if (port->vtcport_invq != NULL)
		virtqueue_disable_intr(port->vtcport_invq);
	if (port->vtcport_outvq != NULL)
		virtqueue_disable_intr(port->vtcport_outvq);
}