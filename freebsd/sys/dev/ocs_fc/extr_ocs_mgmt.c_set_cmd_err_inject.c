#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cmd_err_inject; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  ocs_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_cmd_err_inject(ocs_t *ocs, char *name, char *value)
{
	ocs->cmd_err_inject = ocs_strtoul(value, NULL, 0);
	ocs_log_debug(ocs, "mgmt set: %s %s\n", name, value);
	return 0;
}