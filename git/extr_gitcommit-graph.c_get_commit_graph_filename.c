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
 char* xstrfmt (char*,char const*) ; 

char *get_commit_graph_filename(const char *obj_dir)
{
	return xstrfmt("%s/info/commit-graph", obj_dir);
}