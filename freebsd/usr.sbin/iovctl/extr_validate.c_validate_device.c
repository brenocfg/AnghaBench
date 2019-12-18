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
 int /*<<< orphan*/  validate_subsystem (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
validate_device(const nvlist_t *device, const nvlist_t *schema,
    const char *config_name)
{

	validate_subsystem(device, schema, DRIVER_CONFIG_NAME, config_name);
	validate_subsystem(device, schema, IOV_CONFIG_NAME, config_name);
}