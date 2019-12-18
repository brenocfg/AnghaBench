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
typedef  scalar_t__ u64 ;
struct drmem_lmb {scalar_t__ base_addr; } ;
struct TYPE_2__ {int n_lmbs; struct drmem_lmb* lmbs; } ;

/* Variables and functions */
 TYPE_1__* drmem_info ; 
 scalar_t__ drmem_lmb_size () ; 

u64 drmem_lmb_memory_max(void)
{
	struct drmem_lmb *last_lmb;

	last_lmb = &drmem_info->lmbs[drmem_info->n_lmbs - 1];
	return last_lmb->base_addr + drmem_lmb_size();
}