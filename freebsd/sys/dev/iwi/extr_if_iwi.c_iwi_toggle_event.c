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

/* Variables and functions */
 int IWI_RST_GATE_ADMA ; 
 int IWI_RST_GATE_IDMA ; 
 int IWI_RST_GATE_ODMA ; 
 int IWI_RST_STANDBY ; 

__attribute__((used)) static __inline uint32_t
iwi_toggle_event(uint32_t r)
{
	return r &~ (IWI_RST_STANDBY | IWI_RST_GATE_ODMA |
		     IWI_RST_GATE_IDMA | IWI_RST_GATE_ADMA);
}