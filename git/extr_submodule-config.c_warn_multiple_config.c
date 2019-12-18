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
struct object_id {int dummy; } ;

/* Variables and functions */
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*,char const*) ; 

__attribute__((used)) static void warn_multiple_config(const struct object_id *treeish_name,
				 const char *name, const char *option)
{
	const char *commit_string = "WORKTREE";
	if (treeish_name)
		commit_string = oid_to_hex(treeish_name);
	warning("%s:.gitmodules, multiple configurations found for "
			"'submodule.%s.%s'. Skipping second one!",
			commit_string, name, option);
}