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
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  cl_git_write2file (char const*,char const*,int /*<<< orphan*/ ,int,int) ; 

void cl_git_append2file(const char *path, const char *content)
{
	cl_git_write2file(path, content, 0, O_WRONLY | O_CREAT | O_APPEND, 0644);
}