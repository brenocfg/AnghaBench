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
struct tr2_cfg_data {char const* member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_early_config (int /*<<< orphan*/ ,struct tr2_cfg_data*) ; 
 int /*<<< orphan*/  tr2_cfg_cb ; 
 scalar_t__ tr2_cfg_load_patterns () ; 

void tr2_cfg_list_config_fl(const char *file, int line)
{
	struct tr2_cfg_data data = { file, line };

	if (tr2_cfg_load_patterns() > 0)
		read_early_config(tr2_cfg_cb, &data);
}