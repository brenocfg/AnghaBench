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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int SLI4_ASIC_GEN_MASK ; 
 int SLI4_ASIC_GEN_SHIFT ; 

__attribute__((used)) static uint8_t
sli_asic_gen(uint32_t val)
{
	return ((val >> SLI4_ASIC_GEN_SHIFT) & SLI4_ASIC_GEN_MASK);
}