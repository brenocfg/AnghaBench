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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct dtsec_regs {int /*<<< orphan*/  macstnaddr2; int /*<<< orphan*/  macstnaddr1; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 

void fman_dtsec_get_mac_address(struct dtsec_regs *regs, uint8_t *macaddr)
{
	uint32_t tmp1, tmp2;

	tmp1 = ioread32be(&regs->macstnaddr1);
	tmp2 = ioread32be(&regs->macstnaddr2);

	macaddr[0] = (uint8_t)((tmp2 & 0x00ff0000) >> 16);
	macaddr[1] = (uint8_t)((tmp2 & 0xff000000) >> 24);
	macaddr[2] = (uint8_t)(tmp1 & 0x000000ff);
	macaddr[3] = (uint8_t)((tmp1 & 0x0000ff00) >> 8);
	macaddr[4] = (uint8_t)((tmp1 & 0x00ff0000) >> 16);
	macaddr[5] = (uint8_t)((tmp1 & 0xff000000) >> 24);
}