#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  ctl_addr; } ;
struct ata_port {TYPE_2__ ioaddr; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sff_set_devctl ) (struct ata_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_sff_set_devctl(struct ata_port *ap, u8 ctl)
{
	if (ap->ops->sff_set_devctl)
		ap->ops->sff_set_devctl(ap, ctl);
	else
		iowrite8(ctl, ap->ioaddr.ctl_addr);
}