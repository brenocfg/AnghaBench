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
struct fetch_config {int /*<<< orphan*/ * recurse_submodules; int /*<<< orphan*/ * max_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_fetch_recurse_submodules_arg (char const*,char const*) ; 
 int /*<<< orphan*/  parse_submodule_fetchjobs (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int gitmodules_fetch_config(const char *var, const char *value, void *cb)
{
	struct fetch_config *config = cb;
	if (!strcmp(var, "submodule.fetchjobs")) {
		*(config->max_children) = parse_submodule_fetchjobs(var, value);
		return 0;
	} else if (!strcmp(var, "fetch.recursesubmodules")) {
		*(config->recurse_submodules) = parse_fetch_recurse_submodules_arg(var, value);
		return 0;
	}

	return 0;
}