#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  pool; TYPE_1__* fs; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct change_node_prop_args {int /*<<< orphan*/  path; TYPE_11__* root; int /*<<< orphan*/ * value; int /*<<< orphan*/  name; } ;
struct TYPE_21__ {int /*<<< orphan*/  node; scalar_t__ parent; } ;
typedef  TYPE_3__ parent_path_t ;
struct TYPE_22__ {scalar_t__ format; } ;
typedef  TYPE_4__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_19__ {TYPE_4__* fsap_data; } ;
struct TYPE_18__ {char* txn; int txn_flags; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_BASE__MIN_MERGEINFO_FORMAT ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_parent_mergeinfo_counts (scalar_t__,int,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_11__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_3__**,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__allow_locked_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_set_has_mergeinfo (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_set_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
txn_body_change_node_prop(void *baton,
                          trail_t *trail)
{
  struct change_node_prop_args *args = baton;
  parent_path_t *parent_path;
  apr_hash_t *proplist;
  const char *txn_id = args->root->txn;
  base_fs_data_t *bfd = trail->fs->fsap_data;

  SVN_ERR(open_path(&parent_path, args->root, args->path, 0, txn_id,
                    trail, trail->pool));

  /* Check to see if path is locked; if so, check that we can use it.
     Notice that we're doing this non-recursively, regardless of node kind. */
  if (args->root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_base__allow_locked_operation
            (args->path, FALSE, trail, trail->pool));

  SVN_ERR(make_path_mutable(args->root, parent_path, args->path,
                            trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_get_proplist(&proplist, parent_path->node,
                                        trail, trail->pool));

  /* If there's no proplist, but we're just deleting a property, exit now. */
  if ((! proplist) && (! args->value))
    return SVN_NO_ERROR;

  /* Now, if there's no proplist, we know we need to make one. */
  if (! proplist)
    proplist = apr_hash_make(trail->pool);

  /* Set the property. */
  svn_hash_sets(proplist, args->name, args->value);

  /* Overwrite the node's proplist. */
  SVN_ERR(svn_fs_base__dag_set_proplist(parent_path->node, proplist,
                                        txn_id, trail, trail->pool));

  /* If this was a change to the mergeinfo property, and our version
     of the filesystem cares, we have some extra recording to do.

     ### If the format *doesn't* support mergeinfo recording, should
     ### we fuss about attempts to change the svn:mergeinfo property
     ### in any way save to delete it?  */
  if ((bfd->format >= SVN_FS_BASE__MIN_MERGEINFO_FORMAT)
      && (strcmp(args->name, SVN_PROP_MERGEINFO) == 0))
    {
      svn_boolean_t had_mergeinfo, has_mergeinfo = args->value != NULL;

      /* First, note on our node that it has mergeinfo. */
      SVN_ERR(svn_fs_base__dag_set_has_mergeinfo(parent_path->node,
                                                 has_mergeinfo,
                                                 &had_mergeinfo, txn_id,
                                                 trail, trail->pool));

      /* If this is a change from the old state, we need to update our
         node's parents' mergeinfo counts by a factor of 1. */
      if (parent_path->parent && ((! had_mergeinfo) != (! has_mergeinfo)))
        SVN_ERR(adjust_parent_mergeinfo_counts(parent_path->parent,
                                               has_mergeinfo ? 1 : -1,
                                               txn_id, trail, trail->pool));
    }

  /* Make a record of this modification in the changes table. */
  return add_change(args->root->fs, txn_id,
                    args->path, svn_fs_base__dag_get_id(parent_path->node),
                    svn_fs_path_change_modify, FALSE, TRUE, trail,
                    trail->pool);
}