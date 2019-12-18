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
struct TYPE_19__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_21__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * id; } ;
typedef  TYPE_3__ svn_fs_dirent_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct get_mergeinfo_data_and_entries_baton {int /*<<< orphan*/  children_atop_mergeinfo_trees; int /*<<< orphan*/  receiver_baton; int /*<<< orphan*/  node_path; int /*<<< orphan*/  (* receiver ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * node; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_mergeinfo_stats (scalar_t__*,int*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_base__dag_node_kind (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_base__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_mergeinfo_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
txn_body_get_mergeinfo_data_and_entries(void *baton, trail_t *trail)
{
  struct get_mergeinfo_data_and_entries_baton *args = baton;
  dag_node_t *node = args->node;
  apr_hash_t *entries;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(trail->pool);
  apr_pool_t *children_pool =
    apr_hash_pool_get(args->children_atop_mergeinfo_trees);

  SVN_ERR_ASSERT(svn_fs_base__dag_node_kind(node) == svn_node_dir);

  SVN_ERR(svn_fs_base__dag_dir_entries(&entries, node, trail, trail->pool));
  for (hi = apr_hash_first(trail->pool, entries); hi; hi = apr_hash_next(hi))
    {
      void *val;
      svn_fs_dirent_t *dirent;
      const svn_fs_id_t *child_id;
      dag_node_t *child_node;
      svn_boolean_t has_mergeinfo;
      apr_int64_t kid_count;

      svn_pool_clear(iterpool);
      apr_hash_this(hi, NULL, NULL, &val);
      dirent = val;
      child_id = dirent->id;

      /* Get the node for this child. */
      SVN_ERR(svn_fs_base__dag_get_node(&child_node, trail->fs, child_id,
                                        trail, iterpool));

      /* Query the child node's mergeinfo stats. */
      SVN_ERR(svn_fs_base__dag_get_mergeinfo_stats(&has_mergeinfo, &kid_count,
                                                   child_node, trail,
                                                   iterpool));

      /* If the child has mergeinfo, add it to the result catalog. */
      if (has_mergeinfo)
        {
          apr_hash_t *plist;
          svn_mergeinfo_t child_mergeinfo;
          svn_string_t *pval;
          svn_error_t *err;

          SVN_ERR(svn_fs_base__dag_get_proplist(&plist, child_node,
                                                trail, iterpool));
          pval = svn_hash_gets(plist, SVN_PROP_MERGEINFO);
          if (! pval)
            {
              svn_string_t *id_str = svn_fs_base__id_unparse(child_id,
                                                             iterpool);
              return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                       _("Node-revision '%s' claims to have "
                                         "mergeinfo but doesn't"),
                                       id_str->data);
            }
          /* Issue #3896: If syntactically invalid mergeinfo is present on
             CHILD_NODE then treat it as if no mergeinfo is present rather
             than raising a parse error. */
          err = svn_mergeinfo_parse(&child_mergeinfo, pval->data,
                                    iterpool);
          if (err)
            {
              if (err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
                svn_error_clear(err);
              else
                return svn_error_trace(err);
            }
          else
            {
              SVN_ERR(args->receiver(svn_fspath__join(args->node_path,
                                                      dirent->name,
                                                      iterpool),
                                     child_mergeinfo,
                                     args->receiver_baton,
                                     iterpool));
            }
        }

      /* If the child has descendants with mergeinfo -- that is, if
         the count of descendants beneath it carrying mergeinfo, not
         including itself, is non-zero -- then add it to the
         children_atop_mergeinfo_trees hash to be crawled later. */
      if ((kid_count - (has_mergeinfo ? 1 : 0)) > 0)
        {
          if (svn_fs_base__dag_node_kind(child_node) != svn_node_dir)
            {
              svn_string_t *id_str = svn_fs_base__id_unparse(child_id,
                                                             iterpool);
              return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                       _("Node-revision '%s' claims to sit "
                                         "atop a tree containing mergeinfo "
                                         "but is not a directory"),
                                       id_str->data);
            }
          svn_hash_sets(args->children_atop_mergeinfo_trees,
                        apr_pstrdup(children_pool, dirent->name),
                        svn_fs_base__dag_dup(child_node, children_pool));
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}