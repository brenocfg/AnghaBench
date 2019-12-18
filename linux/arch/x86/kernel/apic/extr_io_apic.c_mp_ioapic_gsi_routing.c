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
struct mp_ioapic_gsi {int dummy; } ;
struct TYPE_2__ {struct mp_ioapic_gsi gsi_config; } ;

/* Variables and functions */
 TYPE_1__* ioapics ; 

__attribute__((used)) static inline struct mp_ioapic_gsi *mp_ioapic_gsi_routing(int ioapic_idx)
{
	return &ioapics[ioapic_idx].gsi_config;
}