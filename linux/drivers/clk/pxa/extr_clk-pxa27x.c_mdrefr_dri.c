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
 unsigned int SDRAM_TREF ; 
 unsigned int get_sdram_rows () ; 

__attribute__((used)) static u32 mdrefr_dri(unsigned int freq_khz)
{
	u32 interval = freq_khz * SDRAM_TREF / get_sdram_rows();

	return (interval - 31) / 32;
}