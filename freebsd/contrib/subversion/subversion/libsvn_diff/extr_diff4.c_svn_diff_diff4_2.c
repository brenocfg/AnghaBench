#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ type; struct TYPE_10__* next; int /*<<< orphan*/  original_length; int /*<<< orphan*/  modified_length; int /*<<< orphan*/  original_start; int /*<<< orphan*/  modified_start; int /*<<< orphan*/  latest_length; int /*<<< orphan*/  latest_start; } ;
typedef  TYPE_1__ svn_diff_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* token_discard_all ) (void*) ;int /*<<< orphan*/  (* datasources_open ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ svn_diff_fns2_t ;
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
typedef  int /*<<< orphan*/  svn_diff__tree_t ;
typedef  int /*<<< orphan*/  svn_diff__token_index_t ;
typedef  int /*<<< orphan*/  svn_diff__position_t ;
typedef  int /*<<< orphan*/  svn_diff__lcs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  adjust_diff (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 TYPE_1__* svn_diff__diff (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__get_node_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__get_token_counts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__get_tokens (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__lcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__resolve_conflict (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__tree_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_diff__type_conflict ; 
 scalar_t__ svn_diff__type_diff_latest ; 
 scalar_t__ svn_diff__type_diff_modified ; 
 int /*<<< orphan*/  svn_diff_datasource_ancestor ; 
 int /*<<< orphan*/  svn_diff_datasource_latest ; 
 int /*<<< orphan*/  svn_diff_datasource_modified ; 
 int /*<<< orphan*/  svn_diff_datasource_original ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_diff4_2(svn_diff_t **diff,
                 void *diff_baton,
                 const svn_diff_fns2_t *vtable,
                 apr_pool_t *pool)
{
  svn_diff__tree_t *tree;
  svn_diff__position_t *position_list[4];
  svn_diff__token_index_t num_tokens;
  svn_diff__token_index_t *token_counts[4];
  svn_diff_datasource_e datasource[] = {svn_diff_datasource_original,
                                        svn_diff_datasource_modified,
                                        svn_diff_datasource_latest,
                                        svn_diff_datasource_ancestor};
  svn_diff__lcs_t *lcs_ol;
  svn_diff__lcs_t *lcs_adjust;
  svn_diff_t *diff_ol;
  svn_diff_t *diff_adjust;
  svn_diff_t *hunk;
  apr_pool_t *subpool;
  apr_pool_t *subpool2;
  apr_pool_t *subpool3;
  apr_off_t prefix_lines = 0;
  apr_off_t suffix_lines = 0;

  *diff = NULL;

  subpool = svn_pool_create(pool);
  subpool2 = svn_pool_create(subpool);
  subpool3 = svn_pool_create(subpool2);

  svn_diff__tree_create(&tree, subpool3);

  SVN_ERR(vtable->datasources_open(diff_baton, &prefix_lines, &suffix_lines,
                                   datasource, 4));

  SVN_ERR(svn_diff__get_tokens(&position_list[0],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_original,
                               prefix_lines,
                               subpool2));

  SVN_ERR(svn_diff__get_tokens(&position_list[1],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_modified,
                               prefix_lines,
                               subpool));

  SVN_ERR(svn_diff__get_tokens(&position_list[2],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_latest,
                               prefix_lines,
                               subpool));

  SVN_ERR(svn_diff__get_tokens(&position_list[3],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_ancestor,
                               prefix_lines,
                               subpool2));

  num_tokens = svn_diff__get_node_count(tree);

  /* Get rid of the tokens, we don't need them to calc the diff */
  if (vtable->token_discard_all != NULL)
    vtable->token_discard_all(diff_baton);

  /* We don't need the nodes in the tree either anymore, nor the tree itself */
  svn_pool_clear(subpool3);

  token_counts[0] = svn_diff__get_token_counts(position_list[0], num_tokens,
                                               subpool);
  token_counts[1] = svn_diff__get_token_counts(position_list[1], num_tokens,
                                               subpool);
  token_counts[2] = svn_diff__get_token_counts(position_list[2], num_tokens,
                                               subpool);
  token_counts[3] = svn_diff__get_token_counts(position_list[3], num_tokens,
                                               subpool);

  /* Get the lcs for original - latest */
  lcs_ol = svn_diff__lcs(position_list[0], position_list[2],
                         token_counts[0], token_counts[2],
                         num_tokens, prefix_lines,
                         suffix_lines, subpool3);
  diff_ol = svn_diff__diff(lcs_ol, 1, 1, TRUE, pool);

  svn_pool_clear(subpool3);

  for (hunk = diff_ol; hunk; hunk = hunk->next)
    {
      hunk->latest_start = hunk->modified_start;
      hunk->latest_length = hunk->modified_length;
      hunk->modified_start = hunk->original_start;
      hunk->modified_length = hunk->original_length;

      if (hunk->type == svn_diff__type_diff_modified)
          hunk->type = svn_diff__type_diff_latest;
      else
          hunk->type = svn_diff__type_diff_modified;
    }

  /* Get the lcs for common ancestor - original
   * Do reverse adjustments
   */
  lcs_adjust = svn_diff__lcs(position_list[3], position_list[2],
                             token_counts[3], token_counts[2],
                             num_tokens, prefix_lines,
                             suffix_lines, subpool3);
  diff_adjust = svn_diff__diff(lcs_adjust, 1, 1, FALSE, subpool3);
  adjust_diff(diff_ol, diff_adjust);

  svn_pool_clear(subpool3);

  /* Get the lcs for modified - common ancestor
   * Do forward adjustments
   */
  lcs_adjust = svn_diff__lcs(position_list[1], position_list[3],
                             token_counts[1], token_counts[3],
                             num_tokens, prefix_lines,
                             suffix_lines, subpool3);
  diff_adjust = svn_diff__diff(lcs_adjust, 1, 1, FALSE, subpool3);
  adjust_diff(diff_ol, diff_adjust);

  /* Get rid of the position lists for original and ancestor, and delete
   * our scratchpool.
   */
  svn_pool_destroy(subpool2);

  /* Now we try and resolve the conflicts we encountered */
  for (hunk = diff_ol; hunk; hunk = hunk->next)
    {
      if (hunk->type == svn_diff__type_conflict)
        {
          svn_diff__resolve_conflict(hunk, &position_list[1],
                                     &position_list[2], num_tokens, pool);
        }
    }

  svn_pool_destroy(subpool);

  *diff = diff_ol;

  return SVN_NO_ERROR;
}