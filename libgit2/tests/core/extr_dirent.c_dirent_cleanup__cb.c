#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  sub; TYPE_2__* names; } ;
typedef  TYPE_1__ walk_data ;
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_2__ name_data ;

/* Variables and functions */
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_chdir (char*) ; 
 int /*<<< orphan*/  p_rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  top_dir ; 

__attribute__((used)) static void dirent_cleanup__cb(void *_d)
{
	walk_data *d = _d;
	name_data *n;

	for (n = d->names; n->name; n++) {
		cl_must_pass(p_unlink(n->name));
	}

	if (strcmp(d->sub, ".") != 0)
		cl_must_pass(p_rmdir(d->sub));

	cl_must_pass(p_chdir(".."));

	cl_must_pass(p_rmdir(top_dir));

	git_buf_dispose(&d->path);
}