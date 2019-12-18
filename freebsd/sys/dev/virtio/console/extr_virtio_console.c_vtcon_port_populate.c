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
struct vtcon_port {struct virtqueue* vtcport_invq; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  virtqueue_full (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 
 int vtcon_port_create_buf (struct vtcon_port*) ; 

__attribute__((used)) static int
vtcon_port_populate(struct vtcon_port *port)
{
	struct virtqueue *vq;
	int nbufs, error;

	vq = port->vtcport_invq;
	error = ENOSPC;

	for (nbufs = 0; !virtqueue_full(vq); nbufs++) {
		error = vtcon_port_create_buf(port);
		if (error)
			break;
	}

	if (nbufs > 0) {
		virtqueue_notify(vq);
		error = 0;
	}

	return (error);
}