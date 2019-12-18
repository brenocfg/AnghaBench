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
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {TYPE_1__* pb; int /*<<< orphan*/  txn_root; scalar_t__ skipped; } ;
struct node_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; struct revision_baton* rb; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  validate_props; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  change_node_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
remove_node_props(void *baton)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;
  apr_hash_t *proplist;
  apr_hash_index_t *hi;

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    return SVN_NO_ERROR;

  SVN_ERR(svn_fs_node_proplist(&proplist,
                               rb->txn_root, nb->path, nb->pool));

  for (hi = apr_hash_first(nb->pool, proplist); hi; hi = apr_hash_next(hi))
    {
      const char *key = apr_hash_this_key(hi);

      SVN_ERR(change_node_prop(rb->txn_root, nb->path, key, NULL,
                               rb->pb->validate_props, nb->pool));
    }

  return SVN_NO_ERROR;
}