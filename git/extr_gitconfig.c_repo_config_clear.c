#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_configset_clear (TYPE_1__*) ; 

__attribute__((used)) static void repo_config_clear(struct repository *repo)
{
	if (!repo->config || !repo->config->hash_initialized)
		return;
	git_configset_clear(repo->config);
}