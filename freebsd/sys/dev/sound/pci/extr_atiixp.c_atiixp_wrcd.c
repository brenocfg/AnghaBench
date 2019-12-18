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
struct atiixp_info {int codec_idx; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_PHYS_OUT_ADDR ; 
 int ATI_REG_PHYS_OUT_ADDR_EN ; 
 int ATI_REG_PHYS_OUT_ADDR_SHIFT ; 
 int ATI_REG_PHYS_OUT_DATA_SHIFT ; 
 scalar_t__ atiixp_waitready_codec (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atiixp_wrcd(kobj_t obj, void *devinfo, int reg, uint32_t data)
{
	struct atiixp_info *sc = devinfo;

	if (atiixp_waitready_codec(sc))
		return (-1);

	data = (data << ATI_REG_PHYS_OUT_DATA_SHIFT) |
	    (((uint32_t)reg) << ATI_REG_PHYS_OUT_ADDR_SHIFT) |
	    ATI_REG_PHYS_OUT_ADDR_EN | sc->codec_idx;

	atiixp_wr(sc, ATI_REG_PHYS_OUT_ADDR, data);

	return (0);
}