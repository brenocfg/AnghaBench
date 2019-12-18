#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct mergeinfo_diff_baton {int /*<<< orphan*/ * pool; int /*<<< orphan*/  consider_inheritance; void* added; void* deleted; void* to; void* from; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  mergeinfo_hash_diff_cb ; 
 int /*<<< orphan*/ * svn_hash_diff (void*,void*,int /*<<< orphan*/ ,struct mergeinfo_diff_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
walk_mergeinfo_hash_for_diff(svn_mergeinfo_t from, svn_mergeinfo_t to,
                             svn_mergeinfo_t deleted, svn_mergeinfo_t added,
                             svn_boolean_t consider_inheritance,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  struct mergeinfo_diff_baton mdb;
  mdb.from = from;
  mdb.to = to;
  mdb.deleted = deleted;
  mdb.added = added;
  mdb.consider_inheritance = consider_inheritance;
  mdb.pool = result_pool;

  return svn_hash_diff(from, to, mergeinfo_hash_diff_cb, &mdb, scratch_pool);
}