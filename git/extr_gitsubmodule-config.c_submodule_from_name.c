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
struct submodule {int dummy; } ;
struct repository {int /*<<< orphan*/  submodule_cache; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct submodule const* config_from (int /*<<< orphan*/ ,struct object_id const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitmodules_read_check (struct repository*) ; 
 int /*<<< orphan*/  lookup_name ; 

const struct submodule *submodule_from_name(struct repository *r,
					    const struct object_id *treeish_name,
		const char *name)
{
	gitmodules_read_check(r);
	return config_from(r->submodule_cache, treeish_name, name, lookup_name);
}