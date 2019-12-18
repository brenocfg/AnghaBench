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
struct vio_driver_state {int dummy; } ;
struct vdc_port {int /*<<< orphan*/  ldc_reset_timer_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_FOR_LINK_UP ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct vdc_port* to_vdc_port (struct vio_driver_state*) ; 
 int /*<<< orphan*/  vdc_blk_queue_start (struct vdc_port*) ; 
 int /*<<< orphan*/  vdc_finish (struct vio_driver_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdc_handshake_complete(struct vio_driver_state *vio)
{
	struct vdc_port *port = to_vdc_port(vio);

	cancel_delayed_work(&port->ldc_reset_timer_work);
	vdc_finish(vio, 0, WAITING_FOR_LINK_UP);
	vdc_blk_queue_start(port);
}