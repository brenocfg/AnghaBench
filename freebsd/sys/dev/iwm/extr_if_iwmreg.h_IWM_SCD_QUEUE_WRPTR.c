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
 unsigned int IWM_SCD_BASE ; 

__attribute__((used)) static inline unsigned int IWM_SCD_QUEUE_WRPTR(unsigned int chnl)
{
	if (chnl < 20)
		return IWM_SCD_BASE + 0x18 + chnl * 4;
	return IWM_SCD_BASE + 0x284 + (chnl - 20) * 4;
}