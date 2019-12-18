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
typedef  int u8 ;
struct ep93xx_pata_data {int dummy; } ;
struct ata_port {TYPE_2__* ops; TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,unsigned int) ;} ;
struct TYPE_3__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDECTRL_ADDR_LBAL ; 
 int /*<<< orphan*/  IDECTRL_ADDR_NSECT ; 
 int ep93xx_pata_read_reg (struct ep93xx_pata_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pata_write_reg (struct ep93xx_pata_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,unsigned int) ; 

__attribute__((used)) static bool ep93xx_pata_device_is_present(struct ata_port *ap,
					  unsigned int device)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;
	u8 nsect, lbal;

	ap->ops->sff_dev_select(ap, device);

	ep93xx_pata_write_reg(drv_data, 0x55, IDECTRL_ADDR_NSECT);
	ep93xx_pata_write_reg(drv_data, 0xaa, IDECTRL_ADDR_LBAL);

	ep93xx_pata_write_reg(drv_data, 0xaa, IDECTRL_ADDR_NSECT);
	ep93xx_pata_write_reg(drv_data, 0x55, IDECTRL_ADDR_LBAL);

	ep93xx_pata_write_reg(drv_data, 0x55, IDECTRL_ADDR_NSECT);
	ep93xx_pata_write_reg(drv_data, 0xaa, IDECTRL_ADDR_LBAL);

	nsect = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_NSECT);
	lbal = ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_LBAL);

	if ((nsect == 0x55) && (lbal == 0xaa))
		return true;

	return false;
}