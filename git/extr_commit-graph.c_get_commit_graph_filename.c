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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  normalize_path_copy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrfmt (char*,char const*) ; 

char *get_commit_graph_filename(const char *obj_dir)
{
	char *filename = xstrfmt("%s/info/commit-graph", obj_dir);
	char *normalized = xmalloc(strlen(filename) + 1);
	normalize_path_copy(normalized, filename);
	free(filename);
	return normalized;
}