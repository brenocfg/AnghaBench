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
typedef  char const git_config_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int config_error_readonly () ; 

__attribute__((used)) static int config_memory_delete_multivar(git_config_backend *backend, const char *name, const char *regexp)
{
	GIT_UNUSED(backend);
	GIT_UNUSED(name);
	GIT_UNUSED(regexp);
	return config_error_readonly();
}