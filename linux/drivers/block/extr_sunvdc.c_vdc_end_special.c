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
struct vio_disk_desc {int status; } ;
struct vdc_port {int /*<<< orphan*/  vio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_FOR_GEN_CMD ; 
 int /*<<< orphan*/  vdc_finish (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdc_end_special(struct vdc_port *port, struct vio_disk_desc *desc)
{
	int err = desc->status;

	vdc_finish(&port->vio, -err, WAITING_FOR_GEN_CMD);
}