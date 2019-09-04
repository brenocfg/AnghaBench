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
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void update_attr_callback(
	const char *path,
	size_t completed_steps,
	size_t total_steps,
	void *payload)
{
	GIT_UNUSED(completed_steps);
	GIT_UNUSED(total_steps);
	GIT_UNUSED(payload);

	if (path && strcmp(path, "ident1.txt") == 0)
		cl_git_write2file("testrepo/.gitattributes",
			"*.txt ident\n", 12, O_RDWR|O_CREAT, 0666);
}