#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ pci_func; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 int IFM_1000_SX ; 
 int IFM_100_FX ; 
 int IFM_10G_LR ; 
 int IFM_10G_SR ; 
 int /*<<< orphan*/  Q8_LINK_SPEED_0 ; 
 int READ_REG32 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint32_t
qla_get_optics(qla_host_t *ha)
{
	uint32_t link_speed;

	link_speed = READ_REG32(ha, Q8_LINK_SPEED_0);
	if (ha->pci_func == 0)
		link_speed = link_speed & 0xFF;
	else
		link_speed = (link_speed >> 8) & 0xFF;

	switch (link_speed) {
	case 0x1:
		link_speed = IFM_100_FX;
		break;

	case 0x10:
		link_speed = IFM_1000_SX;
		break;

	default:
		link_speed = (IFM_10G_LR | IFM_10G_SR);
		break;
	}

	return(link_speed);
}