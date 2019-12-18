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
struct TYPE_8__ {scalar_t__ is_outer_most_lock; int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* body ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ is_inner_most_lock; scalar_t__ is_global_lock; TYPE_3__* fs; int /*<<< orphan*/  lock_path; int /*<<< orphan*/ * lock_pool; } ;
typedef  TYPE_1__ with_lock_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/  youngest_rev_cache; int /*<<< orphan*/  has_write_lock; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_10__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_lock_on_filesystem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_lock_flag ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__update_min_unpacked_rev (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__youngest_rev (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
with_some_lock_file(with_lock_baton_t *baton)
{
  apr_pool_t *pool = baton->lock_pool;
  svn_error_t *err = get_lock_on_filesystem(baton->lock_path, pool);

  if (!err)
    {
      svn_fs_t *fs = baton->fs;
      svn_fs_x__data_t *ffd = fs->fsap_data;

      if (baton->is_global_lock)
        {
          /* set the "got the lock" flag and register reset function */
          apr_pool_cleanup_register(pool,
                                    ffd,
                                    reset_lock_flag,
                                    apr_pool_cleanup_null);
          ffd->has_write_lock = TRUE;
        }

      if (baton->is_inner_most_lock)
        {
          /* Use a separate sub-pool for the actual function body and a few
           * file accesses. So, the lock-pool only contains the file locks.
           */
          apr_pool_t *subpool = svn_pool_create(pool);

          /* nobody else will modify the repo state
             => read HEAD & pack info once */
          err = svn_fs_x__update_min_unpacked_rev(fs, subpool);
          if (!err)
            err = svn_fs_x__youngest_rev(&ffd->youngest_rev_cache, fs,
                                         subpool);

          /* We performed a few file operations. Clean the pool. */
          svn_pool_clear(subpool);

          if (!err)
            err = baton->body(baton->baton, subpool);

          svn_pool_destroy(subpool);
        }
      else
        {
          /* Nested lock level */
          err = baton->body(baton->baton, pool);
        }
    }

  if (baton->is_outer_most_lock)
    svn_pool_destroy(pool);

  return svn_error_trace(err);
}