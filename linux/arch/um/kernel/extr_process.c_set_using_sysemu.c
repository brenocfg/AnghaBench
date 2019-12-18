#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int sysemu_supported ; 
 int /*<<< orphan*/  using_sysemu ; 

void set_using_sysemu(int value)
{
	if (value > sysemu_supported)
		return;
	atomic_set(&using_sysemu, value);
}