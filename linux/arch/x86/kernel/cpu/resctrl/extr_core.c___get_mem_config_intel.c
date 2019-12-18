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
struct TYPE_4__ {scalar_t__ cos_max; } ;
union cpuid_0x10_x_edx {TYPE_1__ split; int /*<<< orphan*/  full; } ;
struct TYPE_5__ {void* max_delay; } ;
union cpuid_0x10_3_eax {TYPE_2__ split; int /*<<< orphan*/  full; } ;
typedef  int u32 ;
struct TYPE_6__ {void* max_delay; int delay_linear; void* bw_gran; void* min_bw; } ;
struct rdt_resource {int data_width; int alloc_capable; int alloc_enabled; TYPE_3__ membw; void* default_ctrl; scalar_t__ num_closid; } ;

/* Variables and functions */
 void* MAX_MBA_BW ; 
 int MBA_IS_LINEAR ; 
 int /*<<< orphan*/  cpuid_count (int,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdt_get_mb_table (struct rdt_resource*) ; 

__attribute__((used)) static bool __get_mem_config_intel(struct rdt_resource *r)
{
	union cpuid_0x10_3_eax eax;
	union cpuid_0x10_x_edx edx;
	u32 ebx, ecx;

	cpuid_count(0x00000010, 3, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	r->membw.max_delay = eax.split.max_delay + 1;
	r->default_ctrl = MAX_MBA_BW;
	if (ecx & MBA_IS_LINEAR) {
		r->membw.delay_linear = true;
		r->membw.min_bw = MAX_MBA_BW - r->membw.max_delay;
		r->membw.bw_gran = MAX_MBA_BW - r->membw.max_delay;
	} else {
		if (!rdt_get_mb_table(r))
			return false;
	}
	r->data_width = 3;

	r->alloc_capable = true;
	r->alloc_enabled = true;

	return true;
}