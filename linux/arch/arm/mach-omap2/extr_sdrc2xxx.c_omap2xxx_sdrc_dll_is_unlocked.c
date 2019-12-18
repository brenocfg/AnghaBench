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

/* Variables and functions */
 int /*<<< orphan*/  SDRC_DLLA_CTRL ; 
 int sdrc_read_reg (int /*<<< orphan*/ ) ; 

u32 omap2xxx_sdrc_dll_is_unlocked(void)
{
	/* dlla and dllb are a set */
	u32 dll_state = sdrc_read_reg(SDRC_DLLA_CTRL);

	if ((dll_state & (1 << 2)) == (1 << 2))
		return 1;
	else
		return 0;
}