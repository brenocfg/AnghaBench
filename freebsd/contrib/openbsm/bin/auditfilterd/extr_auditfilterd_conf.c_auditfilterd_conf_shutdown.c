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
 int /*<<< orphan*/  auditfilter_module_list_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auditfilter_module_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_list ; 

void
auditfilterd_conf_shutdown(void)
{

	auditfilter_module_list_detach(&filter_list);
	auditfilter_module_list_free(&filter_list);
}