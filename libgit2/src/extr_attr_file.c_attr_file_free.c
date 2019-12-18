#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_attr_file__clear_rules (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void attr_file_free(git_attr_file *file)
{
	bool unlock = !git_mutex_lock(&file->lock);
	git_attr_file__clear_rules(file, false);
	git_pool_clear(&file->pool);
	if (unlock)
		git_mutex_unlock(&file->lock);
	git_mutex_free(&file->lock);

	git__memzero(file, sizeof(*file));
	git__free(file);
}