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
typedef  int /*<<< orphan*/  svn_fs_progress_notify_func_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__stats_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  revision_info_t ;
struct TYPE_3__ {void* cancel_baton; int /*<<< orphan*/  cancel_func; void* progress_baton; int /*<<< orphan*/  progress_func; int /*<<< orphan*/ * stats; int /*<<< orphan*/ * fs; void* null_base; scalar_t__ head; int /*<<< orphan*/  revisions; int /*<<< orphan*/  min_unpacked_rev; int /*<<< orphan*/  shard_size; } ;
typedef  TYPE_1__ query_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_fs__min_unpacked_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__shard_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__youngest_rev (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_query(query_t **query,
             svn_fs_t *fs,
             svn_fs_fs__stats_t *stats,
             svn_fs_progress_notify_func_t progress_func,
             void *progress_baton,
             svn_cancel_func_t cancel_func,
             void *cancel_baton,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  *query = apr_pcalloc(result_pool, sizeof(**query));

  /* Read repository dimensions. */
  (*query)->shard_size = svn_fs_fs__shard_size(fs);
  SVN_ERR(svn_fs_fs__youngest_rev(&(*query)->head, fs, scratch_pool));
  SVN_ERR(svn_fs_fs__min_unpacked_rev(&(*query)->min_unpacked_rev, fs,
                                      scratch_pool));

  /* create data containers and caches
   * Note: this assumes that int is at least 32-bits and that we only support
   * 32-bit wide revision numbers (actually 31-bits due to the signedness
   * of both the nelts field of the array and our revision numbers). This
   * means this code will fail on platforms where int is less than 32-bits
   * and the repository has more revisions than int can hold. */
  (*query)->revisions = apr_array_make(result_pool, (int) (*query)->head + 1,
                                       sizeof(revision_info_t *));
  (*query)->null_base = apr_pcalloc(result_pool,
                                    sizeof(*(*query)->null_base));

  /* Store other parameters */
  (*query)->fs = fs;
  (*query)->stats = stats;
  (*query)->progress_func = progress_func;
  (*query)->progress_baton = progress_baton;
  (*query)->cancel_func = cancel_func;
  (*query)->cancel_baton = cancel_baton;

  return SVN_NO_ERROR;
}