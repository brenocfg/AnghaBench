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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ME_ARC2ME_MASK ; 

__attribute__((used)) static void
IFX_MEI_IRQDisable (DSL_DEV_Device_t * pDev)
{
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ARC2ME_MASK,  0x0);
}