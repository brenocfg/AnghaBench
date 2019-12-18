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
typedef  int /*<<< orphan*/  u16 ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_cc_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 bcma_cc_write32_masked(struct bcma_drv_cc *cc, u16 offset,
					 u32 mask, u32 value)
{
	value &= mask;
	value |= bcma_cc_read32(cc, offset) & ~mask;
	bcma_cc_write32(cc, offset, value);

	return value;
}