#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int page_init_done; } ;
struct TYPE_3__ {scalar_t__ npages; int /*<<< orphan*/  pagesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_2__ uvm ; 
 int /*<<< orphan*/  uvm_physseg_init () ; 
 TYPE_1__ uvmexp ; 

__attribute__((used)) static void
setup(void)
{
	/* Prerequisites for running certain calls in uvm_physseg */
	uvmexp.pagesize = PAGE_SIZE;
	uvmexp.npages = 0;
	uvm.page_init_done = false;
	uvm_physseg_init();
}