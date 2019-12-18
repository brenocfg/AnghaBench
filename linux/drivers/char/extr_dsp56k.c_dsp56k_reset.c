#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_2__ {int rd_data_reg_sel; int wd_data; } ;

/* Variables and functions */
 TYPE_1__ sound_ym ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dsp56k_reset(void)
{
	u_char status;
	
	/* Power down the DSP */
	sound_ym.rd_data_reg_sel = 14;
	status = sound_ym.rd_data_reg_sel & 0xef;
	sound_ym.wd_data = status;
	sound_ym.wd_data = status | 0x10;
  
	udelay(10);
  
	/* Power up the DSP */
	sound_ym.rd_data_reg_sel = 14;
	sound_ym.wd_data = sound_ym.rd_data_reg_sel & 0xef;

	return 0;
}