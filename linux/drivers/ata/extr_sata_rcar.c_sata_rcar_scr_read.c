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
typedef  int /*<<< orphan*/  u32 ;
struct ata_link {TYPE_2__* ap; } ;
struct TYPE_3__ {scalar_t__ scr_addr; } ;
struct TYPE_4__ {TYPE_1__ ioaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SCR_ACTIVE ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static int sata_rcar_scr_read(struct ata_link *link, unsigned int sc_reg,
			      u32 *val)
{
	if (sc_reg > SCR_ACTIVE)
		return -EINVAL;

	*val = ioread32(link->ap->ioaddr.scr_addr + (sc_reg << 2));
	return 0;
}