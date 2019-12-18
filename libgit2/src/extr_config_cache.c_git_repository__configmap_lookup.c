#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* configmap_cache; } ;
typedef  TYPE_1__ git_repository ;
typedef  scalar_t__ git_configmap_item ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_CONFIGMAP_NOT_CACHED ; 
 int git_config__configmap_lookup (int*,int /*<<< orphan*/ *,scalar_t__) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_repository__configmap_lookup(int *out, git_repository *repo, git_configmap_item item)
{
	*out = repo->configmap_cache[(int)item];

	if (*out == GIT_CONFIGMAP_NOT_CACHED) {
		int error;
		git_config *config;

		if ((error = git_repository_config__weakptr(&config, repo)) < 0 ||
			(error = git_config__configmap_lookup(out, config, item)) < 0)
			return error;

		repo->configmap_cache[(int)item] = *out;
	}

	return 0;
}