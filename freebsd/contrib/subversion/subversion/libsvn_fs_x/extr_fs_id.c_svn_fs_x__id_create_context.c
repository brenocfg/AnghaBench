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
struct TYPE_7__ {int /*<<< orphan*/ * owner; TYPE_2__* fs; } ;
typedef  TYPE_1__ svn_fs_x__id_context_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_cleanup ; 
 int /*<<< orphan*/  owner_cleanup ; 

svn_fs_x__id_context_t *
svn_fs_x__id_create_context(svn_fs_t *fs,
                            apr_pool_t *result_pool)
{
  svn_fs_x__id_context_t *result = apr_pcalloc(result_pool, sizeof(*result));
  result->fs = fs;
  result->owner = result_pool;

  /* Check for a special case:
     If the owner of the context also owns the FS, there will be no reason
     to notify them of the respective other's cleanup. */
  if (result_pool != fs->pool)
    {
      /* If the context's owner gets cleaned up before FS, we must disconnect
         from the FS. */
      apr_pool_cleanup_register(result_pool,
                                result,
                                owner_cleanup,
                                apr_pool_cleanup_null);

      /* If the FS gets cleaned up before the context's owner, disconnect
         from the FS and remember its path on disk to be able to re-open it
         later if necessary. */
      apr_pool_cleanup_register(fs->pool,
                                result,
                                fs_cleanup,
                                apr_pool_cleanup_null);
    }

  return result;
}