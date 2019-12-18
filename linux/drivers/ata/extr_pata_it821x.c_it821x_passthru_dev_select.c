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
struct it821x_dev {unsigned int last_device; int /*<<< orphan*/ * pio; } ;
struct TYPE_2__ {struct ata_device* device; } ;
struct ata_port {TYPE_1__ link; struct it821x_dev* private_data; } ;
struct ata_device {size_t devno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_dev_select (struct ata_port*,unsigned int) ; 
 int /*<<< orphan*/  it821x_program (struct ata_port*,struct ata_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it821x_passthru_dev_select(struct ata_port *ap,
				       unsigned int device)
{
	struct it821x_dev *itdev = ap->private_data;
	if (itdev && device != itdev->last_device) {
		struct ata_device *adev = &ap->link.device[device];
		it821x_program(ap, adev, itdev->pio[adev->devno]);
		itdev->last_device = device;
	}
	ata_sff_dev_select(ap, device);
}