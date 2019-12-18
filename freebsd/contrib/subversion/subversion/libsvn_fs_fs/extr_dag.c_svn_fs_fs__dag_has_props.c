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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_9__ {TYPE_1__* prop_rep; } ;
typedef  TYPE_2__ node_revision_t ;
struct TYPE_10__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_3__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_8__ {int expanded_size; int /*<<< orphan*/  txn_id; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node_revision (TYPE_2__**,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_fs__get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_has_props(svn_boolean_t *has_props,
                         dag_node_t *node,
                         apr_pool_t *scratch_pool)
{
  node_revision_t *noderev;

  SVN_ERR(get_node_revision(&noderev, node));

  if (! noderev->prop_rep)
    {
      *has_props = FALSE; /* Easy out */
      return SVN_NO_ERROR;
    }

  if (svn_fs_fs__id_txn_used(&noderev->prop_rep->txn_id))
    {
      /* We are in a commit or something. Check actual properties */
      apr_hash_t *proplist;

      SVN_ERR(svn_fs_fs__get_proplist(&proplist, node->fs,
                                      noderev, scratch_pool));

      *has_props = proplist ? (0 < apr_hash_count(proplist)) : FALSE;
    }
  else
    {
      /* Properties are stored as a standard hash stream,
         always ending with "END\n" (4 bytes) */
      *has_props = noderev->prop_rep->expanded_size > 4;
    }

  return SVN_NO_ERROR;
}