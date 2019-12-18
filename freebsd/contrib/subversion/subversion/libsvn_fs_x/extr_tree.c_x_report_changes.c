#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  fs; scalar_t__ is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
struct TYPE_9__ {int /*<<< orphan*/ * vtable; TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_path_change_iterator_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/  context; int /*<<< orphan*/  changes; void* scratch_pool; } ;
typedef  TYPE_3__ fs_revision_changes_iterator_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_3__* apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rev_changes_iterator_vtable ; 
 int /*<<< orphan*/  svn_fs_x__create_changes_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_changes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_x__txn_changes_fetch (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_changes_iterator_vtable ; 

__attribute__((used)) static svn_error_t *
x_report_changes(svn_fs_path_change_iterator_t **iterator,
                 svn_fs_root_t *root,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_fs_path_change_iterator_t *result = apr_pcalloc(result_pool,
                                                      sizeof(*result));
  if (root->is_txn_root)
    {
      apr_hash_t *changed_paths;
      SVN_ERR(svn_fs_x__txn_changes_fetch(&changed_paths, root->fs,
                                          svn_fs_x__root_txn_id(root),
                                          result_pool));

      result->fsap_data = apr_hash_first(result_pool, changed_paths);
      result->vtable = &txn_changes_iterator_vtable;
    }
  else
    {
      /* The block of changes that we retrieve need to live in a separately
         cleanable pool. */
      apr_pool_t *changes_pool = svn_pool_create(result_pool);

      /* Our iteration context info. */
      fs_revision_changes_iterator_data_t *data = apr_pcalloc(result_pool,
                                                              sizeof(*data));

      /* This pool must remain valid as long as ITERATOR lives but will
         be used only for temporary allocations and will be cleaned up
         frequently.  So, this must be a sub-pool of RESULT_POOL. */
      data->scratch_pool = svn_pool_create(result_pool);

      /* Fetch the first block of data. */
      SVN_ERR(svn_fs_x__create_changes_context(&data->context,
                                               root->fs, root->rev,
                                               result_pool, scratch_pool));
      SVN_ERR(svn_fs_x__get_changes(&data->changes, data->context,
                                    changes_pool, scratch_pool));

      /* Return the fully initialized object. */
      result->fsap_data = data;
      result->vtable = &rev_changes_iterator_vtable;
    }

  *iterator = result;

  return SVN_NO_ERROR;
}