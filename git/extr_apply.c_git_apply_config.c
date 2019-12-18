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
 int /*<<< orphan*/  apply_default_ignorewhitespace ; 
 int /*<<< orphan*/  apply_default_whitespace ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_const (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_xmerge_config ; 

__attribute__((used)) static void git_apply_config(void)
{
	git_config_get_string_const("apply.whitespace", &apply_default_whitespace);
	git_config_get_string_const("apply.ignorewhitespace", &apply_default_ignorewhitespace);
	git_config(git_xmerge_config, NULL);
}