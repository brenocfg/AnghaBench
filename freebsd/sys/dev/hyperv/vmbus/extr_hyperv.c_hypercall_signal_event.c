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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  hc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERCALL_SIGNAL_EVENT ; 
 TYPE_1__ hypercall_context ; 
 int /*<<< orphan*/  hypercall_md (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
hypercall_signal_event(bus_addr_t monprm_paddr)
{
	return hypercall_md(hypercall_context.hc_addr,
	    HYPERCALL_SIGNAL_EVENT, monprm_paddr, 0);
}