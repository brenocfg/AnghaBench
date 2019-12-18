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
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_DEBUG_ENABLE_WQ_DUMP ; 
 int /*<<< orphan*/  ocs_debug_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_debug_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_strcasecmp (char*,char*) ; 

__attribute__((used)) static int
set_debug_wq_dump(ocs_t *ocs, char *name, char *value)
{
	int result;

	if (ocs_strcasecmp(value, "false") == 0) {
		ocs_debug_disable(OCS_DEBUG_ENABLE_WQ_DUMP);
		result = 0;
	} else if (ocs_strcasecmp(value, "true") == 0) {
		ocs_debug_enable(OCS_DEBUG_ENABLE_WQ_DUMP);
		result = 0;
	} else {
		result = -1;
	}

	return result;
}