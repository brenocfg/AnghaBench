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
typedef  int /*<<< orphan*/  git_config_foreach_cb ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int git_config_foreach_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int git_config_foreach(
	const git_config *cfg, git_config_foreach_cb cb, void *payload)
{
	return git_config_foreach_match(cfg, NULL, cb, payload);
}