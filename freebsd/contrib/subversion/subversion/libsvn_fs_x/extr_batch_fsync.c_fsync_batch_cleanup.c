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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ to_sync_t ;
struct TYPE_5__ {int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
fsync_batch_cleanup(void *data)
{
  svn_fs_x__batch_fsync_t *batch = data;
  apr_hash_index_t *hi;

  /* Close all files (implicitly) and release memory. */
  for (hi = apr_hash_first(apr_hash_pool_get(batch->files), batch->files);
       hi;
       hi = apr_hash_next(hi))
    {
      to_sync_t *to_sync = apr_hash_this_val(hi);
      svn_pool_destroy(to_sync->pool);
    }

  return APR_SUCCESS;
}