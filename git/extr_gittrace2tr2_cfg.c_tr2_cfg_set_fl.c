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
 int /*<<< orphan*/  tr2_cfg_cb (char const*,char const*,struct tr2_cfg_data*) ; 
 scalar_t__ tr2_cfg_load_patterns () ; 

void tr2_cfg_set_fl(const char *file, int line, const char *key,
		    const char *value)
{
	struct tr2_cfg_data data = { file, line };

	if (tr2_cfg_load_patterns() > 0)
		tr2_cfg_cb(key, value, &data);
}