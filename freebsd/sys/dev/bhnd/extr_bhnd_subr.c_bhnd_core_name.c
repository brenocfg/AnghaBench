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
struct bhnd_core_info {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 char const* bhnd_find_core_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
bhnd_core_name(const struct bhnd_core_info *ci)
{
	return bhnd_find_core_name(ci->vendor, ci->device);
}