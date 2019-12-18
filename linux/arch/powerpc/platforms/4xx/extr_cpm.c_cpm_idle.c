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
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t CPM_IDLE_DOZE ; 
 int /*<<< orphan*/  cpm_idle_doze () ; 
 int /*<<< orphan*/  cpm_idle_wait () ; 
 TYPE_1__* idle_mode ; 

__attribute__((used)) static void cpm_idle(void)
{
	if (idle_mode[CPM_IDLE_DOZE].enabled)
		cpm_idle_doze();
	else
		cpm_idle_wait();
}