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
 int /*<<< orphan*/  async_probe_drv_names ; 
 int parse_option_str (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline bool cmdline_requested_async_probing(const char *drv_name)
{
	return parse_option_str(async_probe_drv_names, drv_name);
}