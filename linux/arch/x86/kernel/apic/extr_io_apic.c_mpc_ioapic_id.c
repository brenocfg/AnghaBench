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
struct TYPE_3__ {int apicid; } ;
struct TYPE_4__ {TYPE_1__ mp_config; } ;

/* Variables and functions */
 TYPE_2__* ioapics ; 

int mpc_ioapic_id(int ioapic_idx)
{
	return ioapics[ioapic_idx].mp_config.apicid;
}