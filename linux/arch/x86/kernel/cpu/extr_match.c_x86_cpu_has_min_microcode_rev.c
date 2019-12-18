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
struct x86_cpu_desc {scalar_t__ x86_microcode_rev; } ;
struct TYPE_2__ {scalar_t__ microcode; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 struct x86_cpu_desc* x86_match_cpu_with_stepping (struct x86_cpu_desc const*) ; 

bool x86_cpu_has_min_microcode_rev(const struct x86_cpu_desc *table)
{
	const struct x86_cpu_desc *res = x86_match_cpu_with_stepping(table);

	if (!res || res->x86_microcode_rev > boot_cpu_data.microcode)
		return false;

	return true;
}