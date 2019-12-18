#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_DIRECTION_FETCH ; 
 int GIT_DIRECTION_PUSH ; 
 int GIT_OK ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (void*,char*) ; 

__attribute__((used)) static int urlresolve_callback(git_buf *url_resolved, const char *url, int direction, void *payload)
{
	cl_assert(strcmp(url, "git://github.com/libgit2/libgit2") == 0);
	cl_assert(strcmp(payload, "payload") == 0);
	cl_assert(url_resolved->size == 0);
	
	if (direction == GIT_DIRECTION_PUSH)
		git_buf_sets(url_resolved, "pushresolve");
	if (direction == GIT_DIRECTION_FETCH)
		git_buf_sets(url_resolved, "fetchresolve");

	return GIT_OK;
}