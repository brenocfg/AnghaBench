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
 int /*<<< orphan*/  generate_info_refs ; 
 char* git_pathdup (char*) ; 
 int update_info_file (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int update_info_refs(int force)
{
	char *path = git_pathdup("info/refs");
	int ret = update_info_file(path, generate_info_refs, force);
	free(path);
	return ret;
}