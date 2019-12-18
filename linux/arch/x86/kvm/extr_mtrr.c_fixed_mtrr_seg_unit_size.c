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
typedef  int u64 ;
struct TYPE_2__ {int range_shift; } ;

/* Variables and functions */
 TYPE_1__* fixed_seg_table ; 

__attribute__((used)) static u64 fixed_mtrr_seg_unit_size(int seg)
{
	return 8 << fixed_seg_table[seg].range_shift;
}