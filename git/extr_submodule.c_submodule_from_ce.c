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
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  should_update_submodules () ; 
 struct submodule const* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

const struct submodule *submodule_from_ce(const struct cache_entry *ce)
{
	if (!S_ISGITLINK(ce->ce_mode))
		return NULL;

	if (!should_update_submodules())
		return NULL;

	return submodule_from_path(the_repository, &null_oid, ce->name);
}