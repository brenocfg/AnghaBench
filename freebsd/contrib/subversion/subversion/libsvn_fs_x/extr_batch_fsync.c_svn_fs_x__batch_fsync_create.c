#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  flush_to_disk; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_batch_cleanup ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitable_counter__create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__batch_fsync_create(svn_fs_x__batch_fsync_t **result_p,
                             svn_boolean_t flush_to_disk,
                             apr_pool_t *result_pool)
{
  svn_fs_x__batch_fsync_t *result = apr_pcalloc(result_pool, sizeof(*result));
  result->files = svn_hash__make(result_pool);
  result->flush_to_disk = flush_to_disk;

  SVN_ERR(waitable_counter__create(&result->counter, result_pool));
  apr_pool_cleanup_register(result_pool, result, fsync_batch_cleanup,
                            apr_pool_cleanup_null);

  *result_p = result;

  return SVN_NO_ERROR;
}