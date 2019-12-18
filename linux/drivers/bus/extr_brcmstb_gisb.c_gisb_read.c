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
typedef  int u32 ;
struct brcmstb_gisb_arb_device {int* gisb_offsets; scalar_t__ base; scalar_t__ big_endian; } ;

/* Variables and functions */
 int ARB_ERR_CAP_MASTER ; 
 int ioread32 (scalar_t__) ; 
 int ioread32be (scalar_t__) ; 

__attribute__((used)) static u32 gisb_read(struct brcmstb_gisb_arb_device *gdev, int reg)
{
	int offset = gdev->gisb_offsets[reg];

	if (offset < 0) {
		/* return 1 if the hardware doesn't have ARB_ERR_CAP_MASTER */
		if (reg == ARB_ERR_CAP_MASTER)
			return 1;
		else
			return 0;
	}

	if (gdev->big_endian)
		return ioread32be(gdev->base + offset);
	else
		return ioread32(gdev->base + offset);
}