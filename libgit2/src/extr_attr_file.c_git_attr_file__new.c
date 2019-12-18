#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_attr_file_source ;
typedef  int /*<<< orphan*/  git_attr_file_entry ;
struct TYPE_7__ {int /*<<< orphan*/  source; int /*<<< orphan*/ * entry; int /*<<< orphan*/  pool; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 

int git_attr_file__new(
	git_attr_file **out,
	git_attr_file_entry *entry,
	git_attr_file_source source)
{
	git_attr_file *attrs = git__calloc(1, sizeof(git_attr_file));
	GIT_ERROR_CHECK_ALLOC(attrs);

	if (git_mutex_init(&attrs->lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to initialize lock");
		git__free(attrs);
		return -1;
	}

	git_pool_init(&attrs->pool, 1);
	GIT_REFCOUNT_INC(attrs);
	attrs->entry  = entry;
	attrs->source = source;
	*out = attrs;
	return 0;
}