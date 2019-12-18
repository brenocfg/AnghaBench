#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
struct TYPE_23__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct get_mergeinfo_for_path_baton {scalar_t__ inherit; int /*<<< orphan*/  pool; int /*<<< orphan*/ ** mergeinfo; scalar_t__ adjust_inherited_mergeinfo; int /*<<< orphan*/  path; int /*<<< orphan*/  root; } ;
struct TYPE_24__ {struct TYPE_24__* parent; int /*<<< orphan*/ * node; } ;
typedef  TYPE_4__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  open_path (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_path_relpath (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs__append_to_merged_froms (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_mergeinfo_stats (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_base__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_mergeinfo_explicit ; 
 int /*<<< orphan*/  svn_mergeinfo_inheritable2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_mergeinfo_nearest_ancestor ; 
 TYPE_3__* svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
txn_body_get_mergeinfo_for_path(void *baton, trail_t *trail)
{
  struct get_mergeinfo_for_path_baton *args = baton;
  parent_path_t *parent_path, *nearest_ancestor;
  apr_hash_t *proplist;
  svn_string_t *mergeinfo_string;
  apr_pool_t *iterpool;
  dag_node_t *node = NULL;

  *(args->mergeinfo) = NULL;

  SVN_ERR(open_path(&parent_path, args->root, args->path, 0,
                    NULL, trail, trail->pool));

  /* Init the nearest ancestor. */
  nearest_ancestor = parent_path;
  if (args->inherit == svn_mergeinfo_nearest_ancestor)
    {
      if (! parent_path->parent)
        return SVN_NO_ERROR;
      nearest_ancestor = parent_path->parent;
    }

  iterpool = svn_pool_create(trail->pool);
  while (TRUE)
    {
      svn_boolean_t has_mergeinfo;
      apr_int64_t count;

      svn_pool_clear(iterpool);

      node = nearest_ancestor->node;
      SVN_ERR(svn_fs_base__dag_get_mergeinfo_stats(&has_mergeinfo, &count,
                                                   node, trail, iterpool));
      if (has_mergeinfo)
        break;

      /* No need to loop if we're looking for explicit mergeinfo. */
      if (args->inherit == svn_mergeinfo_explicit)
        {
          svn_pool_destroy(iterpool);
          return SVN_NO_ERROR;
        }

      nearest_ancestor = nearest_ancestor->parent;

      /* Run out?  There's no mergeinfo. */
      if (! nearest_ancestor)
        {
          svn_pool_destroy(iterpool);
          return SVN_NO_ERROR;
        }
    }
  svn_pool_destroy(iterpool);

  SVN_ERR(svn_fs_base__dag_get_proplist(&proplist, node, trail, trail->pool));
  mergeinfo_string = svn_hash_gets(proplist, SVN_PROP_MERGEINFO);
  if (! mergeinfo_string)
    {
      svn_string_t *id_str =
        svn_fs_base__id_unparse(svn_fs_base__dag_get_id(node), trail->pool);
      return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                               _("Node-revision '%s' claims to have "
                                 "mergeinfo but doesn't"), id_str->data);
    }

  /* Parse the mergeinfo; store the result in ARGS->MERGEINFO. */
  {
    /* Issue #3896: If a node has syntactically invalid mergeinfo, then
       treat it as if no mergeinfo is present rather than raising a parse
       error. */
    svn_error_t *err = svn_mergeinfo_parse(args->mergeinfo,
                                           mergeinfo_string->data,
                                           args->pool);
    if (err)
      {
        if (err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
          {
            svn_error_clear(err);
            err = NULL;
            args->mergeinfo = NULL;
          }
        return svn_error_trace(err);
      }
  }

  /* If our nearest ancestor is the very path we inquired about, we
     can return the mergeinfo results directly.  Otherwise, we're
     inheriting the mergeinfo, so we need to a) remove non-inheritable
     ranges and b) telescope the merged-from paths. */
  if (args->adjust_inherited_mergeinfo && (nearest_ancestor != parent_path))
    {
      svn_mergeinfo_t tmp_mergeinfo;

      SVN_ERR(svn_mergeinfo_inheritable2(&tmp_mergeinfo, *args->mergeinfo,
                                         NULL, SVN_INVALID_REVNUM,
                                         SVN_INVALID_REVNUM, TRUE,
                                         trail->pool, trail->pool));
      SVN_ERR(svn_fs__append_to_merged_froms(args->mergeinfo, tmp_mergeinfo,
                                             parent_path_relpath(
                                               parent_path, nearest_ancestor,
                                               trail->pool),
                                             args->pool));
    }

  return SVN_NO_ERROR;
}