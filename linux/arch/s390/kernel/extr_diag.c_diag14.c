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
struct TYPE_2__ {int (* diag14 ) (unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X014 ; 
 TYPE_1__ diag_dma_ops ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 
 int stub1 (unsigned long,unsigned long,unsigned long) ; 

int diag14(unsigned long rx, unsigned long ry1, unsigned long subcode)
{
	diag_stat_inc(DIAG_STAT_X014);
	return diag_dma_ops.diag14(rx, ry1, subcode);
}