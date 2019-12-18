#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  walk_deleted_dirs; int /*<<< orphan*/ * empty_file; void* callback_baton; int /*<<< orphan*/  const* callbacks; int /*<<< orphan*/ * result_pool; } ;
typedef  TYPE_1__ wc_diff_wrap_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_diff_callbacks4_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  file_changed; int /*<<< orphan*/  file_deleted; int /*<<< orphan*/  file_added; int /*<<< orphan*/  file_opened; int /*<<< orphan*/  dir_closed; int /*<<< orphan*/  dir_changed; int /*<<< orphan*/  dir_deleted; int /*<<< orphan*/  dir_added; int /*<<< orphan*/  dir_opened; } ;
typedef  TYPE_2__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* svn_diff__tree_processor_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_dir_added ; 
 int /*<<< orphan*/  wrap_dir_changed ; 
 int /*<<< orphan*/  wrap_dir_closed ; 
 int /*<<< orphan*/  wrap_dir_deleted ; 
 int /*<<< orphan*/  wrap_dir_opened ; 
 int /*<<< orphan*/  wrap_file_added ; 
 int /*<<< orphan*/  wrap_file_changed ; 
 int /*<<< orphan*/  wrap_file_deleted ; 
 int /*<<< orphan*/  wrap_file_opened ; 

svn_error_t *
svn_wc__wrap_diff_callbacks(const svn_diff_tree_processor_t **diff_processor,
                            const svn_wc_diff_callbacks4_t *callbacks,
                            void *callback_baton,
                            svn_boolean_t walk_deleted_dirs,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  wc_diff_wrap_baton_t *wrap_baton;
  svn_diff_tree_processor_t *processor;

  wrap_baton = apr_pcalloc(result_pool, sizeof(*wrap_baton));

  wrap_baton->result_pool = result_pool;
  wrap_baton->callbacks = callbacks;
  wrap_baton->callback_baton = callback_baton;
  wrap_baton->empty_file = NULL;
  wrap_baton->walk_deleted_dirs = walk_deleted_dirs;

  processor = svn_diff__tree_processor_create(wrap_baton, result_pool);

  processor->dir_opened   = wrap_dir_opened;
  processor->dir_added    = wrap_dir_added;
  processor->dir_deleted  = wrap_dir_deleted;
  processor->dir_changed  = wrap_dir_changed;
  processor->dir_closed   = wrap_dir_closed;

  processor->file_opened   = wrap_file_opened;
  processor->file_added    = wrap_file_added;
  processor->file_deleted  = wrap_file_deleted;
  processor->file_changed  = wrap_file_changed;
  /*processor->file_closed   = wrap_file_closed*/; /* Not needed */

  *diff_processor = processor;
  return SVN_NO_ERROR;
}