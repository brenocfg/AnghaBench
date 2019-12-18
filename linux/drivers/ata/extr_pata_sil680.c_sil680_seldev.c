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
struct ata_port {int port_no; } ;
struct ata_device {scalar_t__ devno; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long sil680_seldev(struct ata_port *ap, struct ata_device *adev, int r)
{
	unsigned long base = 0xA0 + r;
	base += (ap->port_no << 4);
	base |= adev->devno ? 2 : 0;
	return base;
}