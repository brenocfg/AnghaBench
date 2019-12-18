#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * baseline; } ;
struct TYPE_5__ {int /*<<< orphan*/  attr_session; int /*<<< orphan*/ * mkdir_map; int /*<<< orphan*/ * index; int /*<<< orphan*/  tmp; int /*<<< orphan*/  target_path; int /*<<< orphan*/ * pfx; int /*<<< orphan*/  update_conflicts; int /*<<< orphan*/  remove_conflicts; int /*<<< orphan*/  pool; int /*<<< orphan*/  removes; TYPE_1__ opts; scalar_t__ opts_free_baseline; } ;
typedef  TYPE_2__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_attr_session__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free_deep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void checkout_data_clear(checkout_data *data)
{
	if (data->opts_free_baseline) {
		git_tree_free(data->opts.baseline);
		data->opts.baseline = NULL;
	}

	git_vector_free(&data->removes);
	git_pool_clear(&data->pool);

	git_vector_free_deep(&data->remove_conflicts);
	git_vector_free_deep(&data->update_conflicts);

	git__free(data->pfx);
	data->pfx = NULL;

	git_buf_dispose(&data->target_path);
	git_buf_dispose(&data->tmp);

	git_index_free(data->index);
	data->index = NULL;

	git_strmap_free(data->mkdir_map);
	data->mkdir_map = NULL;

	git_attr_session__free(&data->attr_session);
}