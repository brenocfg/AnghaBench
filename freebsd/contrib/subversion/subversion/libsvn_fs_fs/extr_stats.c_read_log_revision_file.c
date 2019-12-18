#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int shard_size; int /*<<< orphan*/  progress_baton; int /*<<< orphan*/  (* progress_func ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ query_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_log_rev_or_packfile (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_log_revision_file(query_t *query,
                       svn_revnum_t revision,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  SVN_ERR(read_log_rev_or_packfile(query, revision, 1,
                                   result_pool, scratch_pool));

  /* show progress every 1000 revs or so */
  if (query->progress_func)
    {
      if (query->shard_size && (revision % query->shard_size == 0))
        query->progress_func(revision, query->progress_baton, scratch_pool);
      if (!query->shard_size && (revision % 1000 == 0))
        query->progress_func(revision, query->progress_baton, scratch_pool);
    }

  return SVN_NO_ERROR;
}