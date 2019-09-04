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

/* Variables and functions */
 char* git_pathdup (char*,char const*) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int /*<<< orphan*/  relative_marks_paths ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char* make_fast_import_path(const char *path)
{
	if (!relative_marks_paths || is_absolute_path(path))
		return xstrdup(path);
	return git_pathdup("info/fast-import/%s", path);
}