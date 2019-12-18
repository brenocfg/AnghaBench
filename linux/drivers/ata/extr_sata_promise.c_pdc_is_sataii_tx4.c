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
 unsigned long PDC_FLAG_4_PORTS ; 
 unsigned long PDC_FLAG_GEN_II ; 

__attribute__((used)) static int pdc_is_sataii_tx4(unsigned long flags)
{
	const unsigned long mask = PDC_FLAG_GEN_II | PDC_FLAG_4_PORTS;
	return (flags & mask) == mask;
}