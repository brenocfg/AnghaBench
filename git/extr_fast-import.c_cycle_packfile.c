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
 int /*<<< orphan*/  end_packfile () ; 
 int /*<<< orphan*/  start_packfile () ; 

__attribute__((used)) static void cycle_packfile(void)
{
	end_packfile();
	start_packfile();
}