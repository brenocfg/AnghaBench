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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_BOOTABLE_TOKEN ; 
 int /*<<< orphan*/  PATH_DEFAULTS_LOADER_CONF ; 
 int /*<<< orphan*/  PATH_KERNEL ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static bool
sanity_check_currdev(void)
{
	struct stat st;

	return (stat(PATH_DEFAULTS_LOADER_CONF, &st) == 0 ||
#ifdef PATH_BOOTABLE_TOKEN
	    stat(PATH_BOOTABLE_TOKEN, &st) == 0 || /* non-standard layout */
#endif
	    stat(PATH_KERNEL, &st) == 0);
}