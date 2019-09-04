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
typedef  int /*<<< orphan*/  git_global_shutdown_fn ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__n_shutdown_callbacks ; 
 int /*<<< orphan*/ * git__shutdown_callbacks ; 
 int git_atomic_inc (int /*<<< orphan*/ *) ; 

void git__on_shutdown(git_global_shutdown_fn callback)
{
	int count = git_atomic_inc(&git__n_shutdown_callbacks);
	assert(count <= (int) ARRAY_SIZE(git__shutdown_callbacks) && count > 0);
	git__shutdown_callbacks[count - 1] = callback;
}