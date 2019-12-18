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
struct repository {int dummy; } ;
struct TYPE_2__ {scalar_t__ prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  is_inside_work_tree () ; 
 char* prefix_path (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 TYPE_1__* startup_info ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 struct repository* the_repository ; 

__attribute__((used)) static char *resolve_relative_path(struct repository *r, const char *rel)
{
	if (!starts_with(rel, "./") && !starts_with(rel, "../"))
		return NULL;

	if (r != the_repository || !is_inside_work_tree())
		die("relative path syntax can't be used outside working tree.");

	/* die() inside prefix_path() if resolved path is outside worktree */
	return prefix_path(startup_info->prefix,
			   startup_info->prefix ? strlen(startup_info->prefix) : 0,
			   rel);
}