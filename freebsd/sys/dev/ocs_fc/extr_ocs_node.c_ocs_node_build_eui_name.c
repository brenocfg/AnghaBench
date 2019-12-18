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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 

void
ocs_node_build_eui_name(char *buffer, uint32_t buffer_len, uint64_t eui_name)
{
	ocs_memset(buffer, 0, buffer_len);

	ocs_snprintf(buffer, buffer_len, "eui.%016llx", (unsigned long long)eui_name);
}