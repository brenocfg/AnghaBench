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
typedef  int /*<<< orphan*/  bhnd_devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_find_core_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bhnd_devclass_t
bhnd_core_class(const struct bhnd_core_info *ci)
{
	return bhnd_find_core_class(ci->vendor, ci->device);
}