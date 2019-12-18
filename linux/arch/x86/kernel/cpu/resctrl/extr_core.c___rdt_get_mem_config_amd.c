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
struct TYPE_3__ {scalar_t__ cos_max; } ;
union cpuid_0x10_x_edx {TYPE_1__ split; int /*<<< orphan*/  full; } ;
union cpuid_0x10_3_eax {int /*<<< orphan*/  full; } ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int delay_linear; int bw_gran; scalar_t__ min_bw; } ;
struct rdt_resource {int data_width; int alloc_capable; int alloc_enabled; TYPE_2__ membw; int /*<<< orphan*/  default_ctrl; scalar_t__ num_closid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MBA_BW_AMD ; 
 int /*<<< orphan*/  cpuid_count (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __rdt_get_mem_config_amd(struct rdt_resource *r)
{
	union cpuid_0x10_3_eax eax;
	union cpuid_0x10_x_edx edx;
	u32 ebx, ecx;

	cpuid_count(0x80000020, 1, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	r->default_ctrl = MAX_MBA_BW_AMD;

	/* AMD does not use delay */
	r->membw.delay_linear = false;

	r->membw.min_bw = 0;
	r->membw.bw_gran = 1;
	/* Max value is 2048, Data width should be 4 in decimal */
	r->data_width = 4;

	r->alloc_capable = true;
	r->alloc_enabled = true;

	return true;
}