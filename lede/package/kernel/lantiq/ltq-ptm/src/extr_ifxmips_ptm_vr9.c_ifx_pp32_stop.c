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

/* Variables and functions */
 int /*<<< orphan*/  IFX_REG_W32_MASK (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP32_FREEZE ; 

void ifx_pp32_stop(int pp32)
{
    unsigned int mask = 1 << (pp32 << 4);

    /*  halt PP32   */
    IFX_REG_W32_MASK(0, mask, PP32_FREEZE);
}