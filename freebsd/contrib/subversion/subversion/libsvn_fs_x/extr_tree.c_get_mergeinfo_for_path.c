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

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  scalar_t__ svn_mergeinfo_inheritance_t ;
struct TYPE_20__ {int /*<<< orphan*/  node; struct TYPE_20__* parent; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
struct TYPE_21__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ svn_fs_root_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_path_relpath (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs__append_to_merged_froms (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_has_mergeinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_2__**,TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_mergeinfo_explicit ; 
 int /*<<< orphan*/  svn_mergeinfo_inheritable2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_mergeinfo_nearest_ancestor ; 
 TYPE_4__* svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_mergeinfo_for_path(svn_mergeinfo_t *mergeinfo,
                       svn_fs_root_t *rev_root,
                       const char *path,
                       svn_mergeinfo_inheritance_t inherit,
                       svn_boolean_t adjust_inherited_mergeinfo,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_fs_x__dag_path_t *dag_path, *nearest_ancestor;
  apr_hash_t *proplist;
  svn_string_t *mergeinfo_string;

  *mergeinfo = NULL;
  SVN_ERR(svn_fs_x__get_dag_path(&dag_path, rev_root, path, 0, FALSE,
                                 scratch_pool, scratch_pool));

  if (inherit == svn_mergeinfo_nearest_ancestor && ! dag_path->parent)
    return SVN_NO_ERROR;

  if (inherit == svn_mergeinfo_nearest_ancestor)
    nearest_ancestor = dag_path->parent;
  else
    nearest_ancestor = dag_path;

  while (TRUE)
    {
      if (svn_fs_x__dag_has_mergeinfo(nearest_ancestor->node))
        break;

      /* No need to loop if we're looking for explicit mergeinfo. */
      if (inherit == svn_mergeinfo_explicit)
        {
          return SVN_NO_ERROR;
        }

      nearest_ancestor = nearest_ancestor->parent;

      /* Run out?  There's no mergeinfo. */
      if (!nearest_ancestor)
        {
          return SVN_NO_ERROR;
        }
    }

  SVN_ERR(svn_fs_x__dag_get_proplist(&proplist, nearest_ancestor->node,
                                     scratch_pool, scratch_pool));
  mergeinfo_string = svn_hash_gets(proplist, SVN_PROP_MERGEINFO);
  if (!mergeinfo_string)
    return svn_error_createf
      (SVN_ERR_FS_CORRUPT, NULL,
       _("Node-revision '%s@%ld' claims to have mergeinfo but doesn't"),
       parent_path_path(nearest_ancestor, scratch_pool), rev_root->rev);

  /* Parse the mergeinfo; store the result in *MERGEINFO. */
  {
    /* Issue #3896: If a node has syntactically invalid mergeinfo, then
       treat it as if no mergeinfo is present rather than raising a parse
       error. */
    svn_error_t *err = svn_mergeinfo_parse(mergeinfo,
                                           mergeinfo_string->data,
                                           result_pool);
    if (err)
      {
        if (err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
          {
            svn_error_clear(err);
            err = NULL;
            *mergeinfo = NULL;
          }
        return svn_error_trace(err);
      }
  }

  /* If our nearest ancestor is the very path we inquired about, we
     can return the mergeinfo results directly.  Otherwise, we're
     inheriting the mergeinfo, so we need to a) remove non-inheritable
     ranges and b) telescope the merged-from paths. */
  if (adjust_inherited_mergeinfo && (nearest_ancestor != dag_path))
    {
      svn_mergeinfo_t tmp_mergeinfo;

      SVN_ERR(svn_mergeinfo_inheritable2(&tmp_mergeinfo, *mergeinfo,
                                         NULL, SVN_INVALID_REVNUM,
                                         SVN_INVALID_REVNUM, TRUE,
                                         scratch_pool, scratch_pool));
      SVN_ERR(svn_fs__append_to_merged_froms(mergeinfo, tmp_mergeinfo,
                                             parent_path_relpath(
                                               dag_path, nearest_ancestor,
                                               scratch_pool),
                                             result_pool));
    }

  return SVN_NO_ERROR;
}