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
struct TYPE_4__ {int (* set ) (TYPE_1__*,char const*,char const*) ;} ;
typedef  TYPE_1__ git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_USE_SET ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/ * GIT_REFCOUNT_OWNER (int /*<<< orphan*/ *) ; 
 scalar_t__ get_backend_for_use (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup_cache_clear (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,char const*,char const*) ; 

int git_config_set_string(git_config *cfg, const char *name, const char *value)
{
	int error;
	git_config_backend *backend;

	if (!value) {
		git_error_set(GIT_ERROR_CONFIG, "the value to set cannot be NULL");
		return -1;
	}

	if (get_backend_for_use(&backend, cfg, name, BACKEND_USE_SET) < 0)
		return GIT_ENOTFOUND;

	error = backend->set(backend, name, value);

	if (!error && GIT_REFCOUNT_OWNER(cfg) != NULL)
		git_repository__configmap_lookup_cache_clear(GIT_REFCOUNT_OWNER(cfg));

	return error;
}