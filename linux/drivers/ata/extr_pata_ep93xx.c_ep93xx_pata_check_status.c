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
struct ep93xx_pata_data {int dummy; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDECTRL_ADDR_STATUS ; 
 int /*<<< orphan*/  ep93xx_pata_read_reg (struct ep93xx_pata_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ep93xx_pata_check_status(struct ata_port *ap)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;

	return ep93xx_pata_read_reg(drv_data, IDECTRL_ADDR_STATUS);
}