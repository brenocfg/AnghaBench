#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x86_model; scalar_t__ x86_max_cores; } ;
struct TYPE_5__ {scalar_t__ num_boxes; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_descs; } ;

/* Variables and functions */
 TYPE_3__ boot_cpu_data ; 
 int /*<<< orphan*/  nhmex_msr_uncores ; 
 TYPE_2__ nhmex_uncore_cbox ; 
 TYPE_1__ nhmex_uncore_mbox ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 
 int uncore_nhmex ; 
 int /*<<< orphan*/  wsmex_uncore_mbox_events ; 

void nhmex_uncore_cpu_init(void)
{
	if (boot_cpu_data.x86_model == 46)
		uncore_nhmex = true;
	else
		nhmex_uncore_mbox.event_descs = wsmex_uncore_mbox_events;
	if (nhmex_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		nhmex_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = nhmex_msr_uncores;
}