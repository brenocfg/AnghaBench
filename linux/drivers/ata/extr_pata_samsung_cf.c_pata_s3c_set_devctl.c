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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_addr; } ;
struct ata_port {TYPE_1__ ioaddr; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pata_s3c_set_devctl(struct ata_port *ap, u8 ctl)
{
	ata_outb(ap->host, ctl, ap->ioaddr.ctl_addr);
}