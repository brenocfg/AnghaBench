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
struct TYPE_4__ {int (* set_multivar ) (TYPE_1__*,char const*,char const*,char const*) ;} ;
typedef  TYPE_1__ git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_USE_DELETE ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ get_backend_for_use (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,char const*,char const*,char const*) ; 

int git_config_set_multivar(git_config *cfg, const char *name, const char *regexp, const char *value)
{
	git_config_backend *backend;

	if (get_backend_for_use(&backend, cfg, name, BACKEND_USE_DELETE) < 0)
		return GIT_ENOTFOUND;

	return backend->set_multivar(backend, name, regexp, value);
}