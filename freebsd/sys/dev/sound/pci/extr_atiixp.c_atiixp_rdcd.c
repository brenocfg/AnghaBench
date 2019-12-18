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
typedef  int uint32_t ;
struct atiixp_info {int codec_idx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_PHYS_IN_ADDR ; 
 int ATI_REG_PHYS_IN_DATA_SHIFT ; 
 int ATI_REG_PHYS_IN_READ_FLAG ; 
 int /*<<< orphan*/  ATI_REG_PHYS_OUT_ADDR ; 
 int ATI_REG_PHYS_OUT_ADDR_EN ; 
 int ATI_REG_PHYS_OUT_ADDR_SHIFT ; 
 int ATI_REG_PHYS_OUT_RW ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int atiixp_rd (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ atiixp_waitready_codec (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
atiixp_rdcd(kobj_t obj, void *devinfo, int reg)
{
	struct atiixp_info *sc = devinfo;
	uint32_t data;
	int timeout;

	if (atiixp_waitready_codec(sc))
		return (-1);

	data = (reg << ATI_REG_PHYS_OUT_ADDR_SHIFT) |
	    ATI_REG_PHYS_OUT_ADDR_EN | ATI_REG_PHYS_OUT_RW | sc->codec_idx;

	atiixp_wr(sc, ATI_REG_PHYS_OUT_ADDR, data);

	if (atiixp_waitready_codec(sc))
		return (-1);

	timeout = 500;
	do {
		data = atiixp_rd(sc, ATI_REG_PHYS_IN_ADDR);
		if (data & ATI_REG_PHYS_IN_READ_FLAG)
			return (data >> ATI_REG_PHYS_IN_DATA_SHIFT);
		DELAY(1);
	} while (--timeout);

	if (reg < 0x7c)
		device_printf(sc->dev, "codec read timeout! (reg 0x%x)\n", reg);

	return (-1);
}