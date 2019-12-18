#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {void* deletions; int /*<<< orphan*/ * changed_paths; } ;
typedef  TYPE_1__ process_changes_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_txn_changes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_changes ; 
 int /*<<< orphan*/  svn_fs_fs__read_changes_incrementally (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__txn_changes_fetch(apr_hash_t **changed_paths_p,
                             svn_fs_t *fs,
                             const svn_fs_fs__id_part_t *txn_id,
                             apr_pool_t *pool)
{
  apr_file_t *file;
  apr_hash_t *changed_paths = apr_hash_make(pool);
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  process_changes_baton_t baton;

  baton.changed_paths = changed_paths;
  baton.deletions = apr_hash_make(scratch_pool);

  SVN_ERR(svn_io_file_open(&file,
                           path_txn_changes(fs, txn_id, scratch_pool),
                           APR_READ | APR_BUFFERED, APR_OS_DEFAULT,
                           scratch_pool));

  SVN_ERR(svn_fs_fs__read_changes_incrementally(
                                  svn_stream_from_aprfile2(file, TRUE,
                                                           scratch_pool),
                                  process_changes, &baton,
                                  scratch_pool));
  svn_pool_destroy(scratch_pool);

  *changed_paths_p = changed_paths;

  return SVN_NO_ERROR;
}