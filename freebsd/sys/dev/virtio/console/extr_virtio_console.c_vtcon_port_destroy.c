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
struct vtcon_port {int vtcport_id; int /*<<< orphan*/  vtcport_mtx; int /*<<< orphan*/ * vtcport_outvq; int /*<<< orphan*/ * vtcport_invq; int /*<<< orphan*/ * vtcport_scport; int /*<<< orphan*/ * vtcport_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct vtcon_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtcon_port_destroy(struct vtcon_port *port)
{

	port->vtcport_sc = NULL;
	port->vtcport_scport = NULL;
	port->vtcport_invq = NULL;
	port->vtcport_outvq = NULL;
	port->vtcport_id = -1;
	mtx_destroy(&port->vtcport_mtx);
	free(port, M_DEVBUF);
}