#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* token_discard_all ) (void*) ;int /*<<< orphan*/  (* datasources_open ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ svn_diff_fns2_t ;
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
typedef  int /*<<< orphan*/  svn_diff__tree_t ;
typedef  int /*<<< orphan*/  svn_diff__token_index_t ;
typedef  int /*<<< orphan*/  svn_diff__position_t ;
typedef  int /*<<< orphan*/  svn_diff__lcs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/ * svn_diff__diff (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__get_node_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__get_token_counts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__get_tokens (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__lcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__tree_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_datasource_modified ; 
 int /*<<< orphan*/  svn_diff_datasource_original ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_diff_2(svn_diff_t **diff,
                void *diff_baton,
                const svn_diff_fns2_t *vtable,
                apr_pool_t *pool)
{
  svn_diff__tree_t *tree;
  svn_diff__position_t *position_list[2];
  svn_diff__token_index_t num_tokens;
  svn_diff__token_index_t *token_counts[2];
  svn_diff_datasource_e datasource[] = {svn_diff_datasource_original,
                                        svn_diff_datasource_modified};
  svn_diff__lcs_t *lcs;
  apr_pool_t *subpool;
  apr_pool_t *treepool;
  apr_off_t prefix_lines = 0;
  apr_off_t suffix_lines = 0;

  *diff = NULL;

  subpool = svn_pool_create(pool);
  treepool = svn_pool_create(pool);

  svn_diff__tree_create(&tree, treepool);

  SVN_ERR(vtable->datasources_open(diff_baton, &prefix_lines, &suffix_lines,
                                   datasource, 2));

  /* Insert the data into the tree */
  SVN_ERR(svn_diff__get_tokens(&position_list[0],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_original,
                               prefix_lines,
                               subpool));

  SVN_ERR(svn_diff__get_tokens(&position_list[1],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_modified,
                               prefix_lines,
                               subpool));

  num_tokens = svn_diff__get_node_count(tree);

  /* The cool part is that we don't need the tokens anymore.
   * Allow the app to clean them up if it wants to.
   */
  if (vtable->token_discard_all != NULL)
    vtable->token_discard_all(diff_baton);

  /* We don't need the nodes in the tree either anymore, nor the tree itself */
  svn_pool_destroy(treepool);

  token_counts[0] = svn_diff__get_token_counts(position_list[0], num_tokens,
                                               subpool);
  token_counts[1] = svn_diff__get_token_counts(position_list[1], num_tokens,
                                               subpool);

  /* Get the lcs */
  lcs = svn_diff__lcs(position_list[0], position_list[1], token_counts[0],
                      token_counts[1], num_tokens, prefix_lines,
                      suffix_lines, subpool);

  /* Produce the diff */
  *diff = svn_diff__diff(lcs, 1, 1, TRUE, pool);

  /* Get rid of all the data we don't have a use for anymore */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}