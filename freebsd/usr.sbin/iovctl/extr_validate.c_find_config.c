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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_CONFIG_NAME ; 
 int /*<<< orphan*/  IOV_CONFIG_NAME ; 
 int /*<<< orphan*/  NV_FLAG_IGNORE_CASE ; 
 int /*<<< orphan*/ * dnvlist_take_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nvlist_t *
find_config(nvlist_t *config, const char * device)
{
	nvlist_t *subsystem, *empty_driver, *empty_iov;

	subsystem = dnvlist_take_nvlist(config, device, NULL);

	if (subsystem != NULL)
		return (subsystem);

	empty_driver = nvlist_create(NV_FLAG_IGNORE_CASE);
	if (empty_driver == NULL)
		err(1, "Could not allocate config nvlist");

	empty_iov = nvlist_create(NV_FLAG_IGNORE_CASE);
	if (empty_iov == NULL)
		err(1, "Could not allocate config nvlist");

	subsystem = nvlist_create(NV_FLAG_IGNORE_CASE);
	if (subsystem == NULL)
		err(1, "Could not allocate config nvlist");

	nvlist_move_nvlist(subsystem, DRIVER_CONFIG_NAME, empty_driver);
	nvlist_move_nvlist(subsystem, IOV_CONFIG_NAME, empty_iov);

	return (subsystem);
}