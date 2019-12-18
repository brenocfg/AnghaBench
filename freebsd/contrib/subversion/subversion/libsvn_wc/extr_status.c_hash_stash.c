#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_status3_t ;
struct TYPE_2__ {int /*<<< orphan*/  op_root; int /*<<< orphan*/  has_descendants; } ;
typedef  TYPE_1__ svn_wc__internal_status_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 void* svn_wc_dup_status3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hash_stash(void *baton,
           const char *path,
           const svn_wc_status3_t *status,
           apr_pool_t *scratch_pool)
{
  apr_hash_t *stat_hash = baton;
  apr_pool_t *hash_pool = apr_hash_pool_get(stat_hash);
  void *new_status = svn_wc_dup_status3(status, hash_pool);
  const svn_wc__internal_status_t *old_status = (const void*)status;

  /* Copy the internal/private data. */
  svn_wc__internal_status_t *is = new_status;
  is->has_descendants = old_status->has_descendants;
  is->op_root = old_status->op_root;

  assert(! svn_hash_gets(stat_hash, path));
  svn_hash_sets(stat_hash, apr_pstrdup(hash_pool, path), new_status);

  return SVN_NO_ERROR;
}