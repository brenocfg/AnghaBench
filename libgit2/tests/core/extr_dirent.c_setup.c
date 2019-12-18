#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* names; int /*<<< orphan*/  sub; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ walk_data ;
struct TYPE_6__ {scalar_t__ count; scalar_t__ name; } ;
typedef  TYPE_2__ name_data ;
typedef  scalar_t__ git_file ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 scalar_t__ p_creat (scalar_t__,int) ; 
 int /*<<< orphan*/  p_mkdir (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* state_loc ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  top_dir ; 

__attribute__((used)) static void setup(walk_data *d)
{
	name_data *n;

	cl_must_pass(p_mkdir(top_dir, 0777));

	cl_must_pass(p_chdir(top_dir));

	if (strcmp(d->sub, ".") != 0)
		cl_must_pass(p_mkdir(d->sub, 0777));

	cl_git_pass(git_buf_sets(&d->path, d->sub));

	state_loc = d;

	for (n = d->names; n->name; n++) {
		git_file fd = p_creat(n->name, 0666);
		cl_assert(fd >= 0);
		p_close(fd);
		n->count = 0;
	}
}