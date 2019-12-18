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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ pa; } ;

/* Variables and functions */
 TYPE_1__* _cm_bases ; 

__attribute__((used)) static u32 omap4_cminst_xlate_clkctrl(u8 part, u16 inst, u16 offset)
{
	return _cm_bases[part].pa + inst + offset;
}