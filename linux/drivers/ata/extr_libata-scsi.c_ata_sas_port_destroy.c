#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_stop ) (struct ata_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 

void ata_sas_port_destroy(struct ata_port *ap)
{
	if (ap->ops->port_stop)
		ap->ops->port_stop(ap);
	kfree(ap);
}