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
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  rerere_autoupdate ; 
 int /*<<< orphan*/  rerere_enabled ; 

__attribute__((used)) static void git_rerere_config(void)
{
	git_config_get_bool("rerere.enabled", &rerere_enabled);
	git_config_get_bool("rerere.autoupdate", &rerere_autoupdate);
	git_config(git_default_config, NULL);
}