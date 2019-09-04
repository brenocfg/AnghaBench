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
 int /*<<< orphan*/  current_time () ; 
 int /*<<< orphan*/  dl_get_memory_used () ; 
 int /*<<< orphan*/  dyn_used_memory () ; 
 int /*<<< orphan*/  st_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void memory_statistic () {
  st_printf ("[%6.2f] Used z-memory = $1%ld$^, Used dl-memory = $1%lld$^\n", current_time(), dyn_used_memory(), dl_get_memory_used());
}