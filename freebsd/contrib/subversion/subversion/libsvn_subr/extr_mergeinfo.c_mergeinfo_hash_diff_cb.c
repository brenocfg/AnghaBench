#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct mergeinfo_diff_baton {int /*<<< orphan*/  pool; scalar_t__ added; int /*<<< orphan*/  to; scalar_t__ deleted; int /*<<< orphan*/  from; int /*<<< orphan*/  consider_inheritance; } ;
typedef  enum svn_hash_diff_key_status { ____Placeholder_svn_hash_diff_key_status } svn_hash_diff_key_status ;
typedef  int /*<<< orphan*/  apr_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_hash_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int svn_hash_diff_key_a ; 
 int svn_hash_diff_key_b ; 
 int svn_hash_diff_key_both ; 
 int /*<<< orphan*/  svn_rangelist_diff (TYPE_1__**,TYPE_1__**,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_rangelist_dup (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_hash_diff_cb(const void *key, apr_ssize_t klen,
                       enum svn_hash_diff_key_status status,
                       void *baton)
{
  /* hash_a is FROM mergeinfo,
     hash_b is TO mergeinfo. */
  struct mergeinfo_diff_baton *cb = baton;
  svn_rangelist_t *from_rangelist, *to_rangelist;
  const char *path = key;
  if (status == svn_hash_diff_key_both)
    {
      /* Record any deltas (additions or deletions). */
      svn_rangelist_t *deleted_rangelist, *added_rangelist;
      from_rangelist = apr_hash_get(cb->from, path, klen);
      to_rangelist = apr_hash_get(cb->to, path, klen);
      SVN_ERR(svn_rangelist_diff(&deleted_rangelist, &added_rangelist,
                                 from_rangelist, to_rangelist,
                                 cb->consider_inheritance, cb->pool));
      if (cb->deleted && deleted_rangelist->nelts > 0)
        apr_hash_set(cb->deleted, apr_pstrmemdup(cb->pool, path, klen),
                     klen, deleted_rangelist);
      if (cb->added && added_rangelist->nelts > 0)
        apr_hash_set(cb->added, apr_pstrmemdup(cb->pool, path, klen),
                     klen, added_rangelist);
    }
  else if ((status == svn_hash_diff_key_a) && cb->deleted)
    {
      from_rangelist = apr_hash_get(cb->from, path, klen);
      apr_hash_set(cb->deleted, apr_pstrmemdup(cb->pool, path, klen), klen,
                   svn_rangelist_dup(from_rangelist, cb->pool));
    }
  else if ((status == svn_hash_diff_key_b) && cb->added)
    {
      to_rangelist = apr_hash_get(cb->to, path, klen);
      apr_hash_set(cb->added, apr_pstrmemdup(cb->pool, path, klen), klen,
                   svn_rangelist_dup(to_rangelist, cb->pool));
    }
  return SVN_NO_ERROR;
}