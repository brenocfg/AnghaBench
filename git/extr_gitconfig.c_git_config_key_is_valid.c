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
 int /*<<< orphan*/  git_config_parse_key_1 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int git_config_key_is_valid(const char *key)
{
	return !git_config_parse_key_1(key, NULL, NULL, 1);
}