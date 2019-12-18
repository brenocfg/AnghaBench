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
struct attr_check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_all_attrs (int /*<<< orphan*/ *,char*,struct attr_check*) ; 
 int /*<<< orphan*/  git_check_attr (int /*<<< orphan*/ *,char*,struct attr_check*) ; 
 int /*<<< orphan*/  output_attr (struct attr_check*,char const*) ; 
 char* prefix_path (char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static void check_attr(const char *prefix,
		       struct attr_check *check,
		       int collect_all,
		       const char *file)
{
	char *full_path =
		prefix_path(prefix, prefix ? strlen(prefix) : 0, file);

	if (collect_all) {
		git_all_attrs(&the_index, full_path, check);
	} else {
		git_check_attr(&the_index, full_path, check);
	}
	output_attr(check, file);

	free(full_path);
}