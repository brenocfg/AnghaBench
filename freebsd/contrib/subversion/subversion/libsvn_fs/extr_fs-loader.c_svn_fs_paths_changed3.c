#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_root_t ;
struct TYPE_12__ {int /*<<< orphan*/ * vtable; TYPE_4__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_path_change_iterator_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  hi; } ;
typedef  TYPE_4__ fsap_iterator_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* report_changes ) (TYPE_3__**,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* paths_changed ) (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_EMULATE_REPORT_CHANGES ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iterator_vtable ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_paths_changed3(svn_fs_path_change_iterator_t **iterator,
                      svn_fs_root_t *root,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_boolean_t emulate =    !root->vtable->report_changes
                          || (   SVN_FS_EMULATE_REPORT_CHANGES
                              && root->vtable->paths_changed);

  if (emulate)
    {
      svn_fs_path_change_iterator_t *result;
      fsap_iterator_data_t *data;

      apr_hash_t *changes;
      SVN_ERR(root->vtable->paths_changed(&changes, root, result_pool));

      data = apr_pcalloc(result_pool, sizeof(*data));
      data->hi = apr_hash_first(result_pool, changes);

      result = apr_pcalloc(result_pool, sizeof(*result));
      result->fsap_data = data;
      result->vtable = &iterator_vtable;

      *iterator = result;
    }
  else
    {
      SVN_ERR(root->vtable->report_changes(iterator, root, result_pool,
                                           scratch_pool));
    }

  return SVN_NO_ERROR;
}