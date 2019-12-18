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
struct repository {int /*<<< orphan*/  submodule_cache; } ;
struct parse_config_parameter {int overwrite; int /*<<< orphan*/ * gitmodules_oid; int /*<<< orphan*/ * treeish_name; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_oid ; 
 int parse_config (char const*,char const*,struct parse_config_parameter*) ; 

__attribute__((used)) static int gitmodules_cb(const char *var, const char *value, void *data)
{
	struct repository *repo = data;
	struct parse_config_parameter parameter;

	parameter.cache = repo->submodule_cache;
	parameter.treeish_name = NULL;
	parameter.gitmodules_oid = &null_oid;
	parameter.overwrite = 1;

	return parse_config(var, value, &parameter);
}