#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ min_unpacked_rev; scalar_t__ shard_size; scalar_t__ head; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ query_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_log_pack_file (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_log_revision_file (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_phys_pack_file (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_phys_revision_file (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_revisions(query_t *query,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_revnum_t revision;

  /* read all packed revs */
  for ( revision = 0
      ; revision < query->min_unpacked_rev
      ; revision += query->shard_size)
    {
      svn_pool_clear(iterpool);

      if (svn_fs_fs__use_log_addressing(query->fs))
        SVN_ERR(read_log_pack_file(query, revision, result_pool, iterpool));
      else
        SVN_ERR(read_phys_pack_file(query, revision, result_pool, iterpool));
    }

  /* read non-packed revs */
  for ( ; revision <= query->head; ++revision)
    {
      svn_pool_clear(iterpool);

      if (svn_fs_fs__use_log_addressing(query->fs))
        SVN_ERR(read_log_revision_file(query, revision, result_pool,
                                       iterpool));
      else
        SVN_ERR(read_phys_revision_file(query, revision, result_pool,
                                        iterpool));
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}