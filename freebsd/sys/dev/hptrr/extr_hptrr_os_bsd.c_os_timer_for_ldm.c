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
struct TYPE_2__ {scalar_t__ vbus; } ;
typedef  TYPE_1__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;

/* Variables and functions */
 int /*<<< orphan*/  ldm_on_timer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void os_timer_for_ldm(void *arg)
{
	PVBUS_EXT vbus_ext = (PVBUS_EXT)arg;
	ldm_on_timer((PVBUS)vbus_ext->vbus);
}