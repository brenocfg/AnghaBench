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
typedef  int u32 ;
struct TYPE_2__ {int (* read_pic ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* pcr_ops ; 
 int stub1 (int) ; 

__attribute__((used)) static u32 sparc_vt_read_pmc(int idx)
{
	u64 val = pcr_ops->read_pic(idx);

	return val & 0xffffffff;
}