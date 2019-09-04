#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_level_t ;
struct TYPE_10__ {int /*<<< orphan*/  backends; } ;
typedef  TYPE_2__ git_config ;
struct TYPE_11__ {TYPE_1__* backend; } ;
typedef  TYPE_3__ backend_internal ;
struct TYPE_9__ {TYPE_2__* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_3__*) ; 
 int /*<<< orphan*/  duplicate_level ; 
 int git_vector_insert_sorted (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_remove_existing_backend (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_config__add_internal(
	git_config *cfg,
	backend_internal *internal,
	git_config_level_t level,
	int force)
{
	int result;

	/* delete existing config backend for level if it exists */
	if (force)
		try_remove_existing_backend(cfg, level);

	if ((result = git_vector_insert_sorted(&cfg->backends,
			internal, &duplicate_level)) < 0)
		return result;

	git_vector_sort(&cfg->backends);
	internal->backend->cfg = cfg;

	GIT_REFCOUNT_INC(internal);

	return 0;
}