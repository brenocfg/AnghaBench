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
struct TYPE_2__ {int /*<<< orphan*/  idle_doze; } ;

/* Variables and functions */
 TYPE_1__ cpm ; 
 int /*<<< orphan*/  cpm_idle_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpm_idle_doze(void)
{
	cpm_idle_sleep(cpm.idle_doze);
}