#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {struct TYPE_17__* next; int /*<<< orphan*/ * resolved_diff; scalar_t__ latest_length; scalar_t__ latest_start; scalar_t__ modified_length; scalar_t__ modified_start; scalar_t__ original_length; scalar_t__ original_start; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ svn_diff_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* token_discard_all ) (void*) ;int /*<<< orphan*/  (* datasources_open ) (void*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ svn_diff_fns2_t ;
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
typedef  int /*<<< orphan*/  svn_diff__tree_t ;
typedef  int /*<<< orphan*/  svn_diff__token_index_t ;
struct TYPE_19__ {scalar_t__ offset; struct TYPE_19__* next; } ;
typedef  TYPE_3__ svn_diff__position_t ;
struct TYPE_20__ {scalar_t__ length; struct TYPE_20__* next; TYPE_3__** position; } ;
typedef  TYPE_4__ svn_diff__lcs_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (void*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  svn_diff__get_node_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__get_token_counts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__get_tokens (TYPE_3__**,int /*<<< orphan*/ *,void*,TYPE_2__ const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_diff__lcs (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__resolve_conflict (TYPE_1__*,TYPE_3__**,TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__tree_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff__type_common ; 
 int /*<<< orphan*/  svn_diff__type_diff_latest ; 
 int /*<<< orphan*/  svn_diff__type_diff_modified ; 
 int /*<<< orphan*/  svn_diff_datasource_latest ; 
 int /*<<< orphan*/  svn_diff_datasource_modified ; 
 int /*<<< orphan*/  svn_diff_datasource_original ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_diff3_2(svn_diff_t **diff,
                 void *diff_baton,
                 const svn_diff_fns2_t *vtable,
                 apr_pool_t *pool)
{
  svn_diff__tree_t *tree;
  svn_diff__position_t *position_list[3];
  svn_diff__token_index_t num_tokens;
  svn_diff__token_index_t *token_counts[3];
  svn_diff_datasource_e datasource[] = {svn_diff_datasource_original,
                                        svn_diff_datasource_modified,
                                        svn_diff_datasource_latest};
  svn_diff__lcs_t *lcs_om;
  svn_diff__lcs_t *lcs_ol;
  apr_pool_t *subpool;
  apr_pool_t *treepool;
  apr_off_t prefix_lines = 0;
  apr_off_t suffix_lines = 0;

  *diff = NULL;

  subpool = svn_pool_create(pool);
  treepool = svn_pool_create(pool);

  svn_diff__tree_create(&tree, treepool);

  SVN_ERR(vtable->datasources_open(diff_baton, &prefix_lines, &suffix_lines,
                                   datasource, 3));

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

  SVN_ERR(svn_diff__get_tokens(&position_list[2],
                               tree,
                               diff_baton, vtable,
                               svn_diff_datasource_latest,
                               prefix_lines,
                               subpool));

  num_tokens = svn_diff__get_node_count(tree);

  /* Get rid of the tokens, we don't need them to calc the diff */
  if (vtable->token_discard_all != NULL)
    vtable->token_discard_all(diff_baton);

  /* We don't need the nodes in the tree either anymore, nor the tree itself */
  svn_pool_destroy(treepool);

  token_counts[0] = svn_diff__get_token_counts(position_list[0], num_tokens,
                                               subpool);
  token_counts[1] = svn_diff__get_token_counts(position_list[1], num_tokens,
                                               subpool);
  token_counts[2] = svn_diff__get_token_counts(position_list[2], num_tokens,
                                               subpool);

  /* Get the lcs for original-modified and original-latest */
  lcs_om = svn_diff__lcs(position_list[0], position_list[1], token_counts[0],
                         token_counts[1], num_tokens, prefix_lines,
                         suffix_lines, subpool);
  lcs_ol = svn_diff__lcs(position_list[0], position_list[2], token_counts[0],
                         token_counts[2], num_tokens, prefix_lines,
                         suffix_lines, subpool);

  /* Produce a merged diff */
  {
    svn_diff_t **diff_ref = diff;

    apr_off_t original_start = 1;
    apr_off_t modified_start = 1;
    apr_off_t latest_start = 1;
    apr_off_t original_sync;
    apr_off_t modified_sync;
    apr_off_t latest_sync;
    apr_off_t common_length;
    apr_off_t modified_length;
    apr_off_t latest_length;
    svn_boolean_t is_modified;
    svn_boolean_t is_latest;
    svn_diff__position_t sentinel_position[2];

    /* Point the position lists to the start of the list
     * so that common_diff/conflict detection actually is
     * able to work.
     */
    if (position_list[1])
      {
        sentinel_position[0].next = position_list[1]->next;
        sentinel_position[0].offset = position_list[1]->offset + 1;
        position_list[1]->next = &sentinel_position[0];
        position_list[1] = sentinel_position[0].next;
      }
    else
      {
        sentinel_position[0].offset = prefix_lines + 1;
        sentinel_position[0].next = NULL;
        position_list[1] = &sentinel_position[0];
      }

    if (position_list[2])
      {
        sentinel_position[1].next = position_list[2]->next;
        sentinel_position[1].offset = position_list[2]->offset + 1;
        position_list[2]->next = &sentinel_position[1];
        position_list[2] = sentinel_position[1].next;
      }
    else
      {
        sentinel_position[1].offset = prefix_lines + 1;
        sentinel_position[1].next = NULL;
        position_list[2] = &sentinel_position[1];
      }

    while (1)
      {
        /* Find the sync points */
        while (1)
          {
            if (lcs_om->position[0]->offset > lcs_ol->position[0]->offset)
              {
                original_sync = lcs_om->position[0]->offset;

                while (lcs_ol->position[0]->offset + lcs_ol->length
                       < original_sync)
                  lcs_ol = lcs_ol->next;

                /* If the sync point is the EOF, and our current lcs segment
                 * doesn't reach as far as EOF, we need to skip this segment.
                 */
                if (lcs_om->length == 0 && lcs_ol->length > 0
                    && lcs_ol->position[0]->offset + lcs_ol->length
                       == original_sync
                    && lcs_ol->position[1]->offset + lcs_ol->length
                       != lcs_ol->next->position[1]->offset)
                  lcs_ol = lcs_ol->next;

                if (lcs_ol->position[0]->offset <= original_sync)
                    break;
              }
            else
              {
                original_sync = lcs_ol->position[0]->offset;

                while (lcs_om->position[0]->offset + lcs_om->length
                       < original_sync)
                  lcs_om = lcs_om->next;

                /* If the sync point is the EOF, and our current lcs segment
                 * doesn't reach as far as EOF, we need to skip this segment.
                 */
                if (lcs_ol->length == 0 && lcs_om->length > 0
                    && lcs_om->position[0]->offset + lcs_om->length
                       == original_sync
                    && lcs_om->position[1]->offset + lcs_om->length
                       != lcs_om->next->position[1]->offset)
                  lcs_om = lcs_om->next;

                if (lcs_om->position[0]->offset <= original_sync)
                    break;
              }
          }

        modified_sync = lcs_om->position[1]->offset
                      + (original_sync - lcs_om->position[0]->offset);
        latest_sync = lcs_ol->position[1]->offset
                    + (original_sync - lcs_ol->position[0]->offset);

        /* Determine what is modified, if anything */
        is_modified = lcs_om->position[0]->offset - original_start > 0
                      || lcs_om->position[1]->offset - modified_start > 0;

        is_latest = lcs_ol->position[0]->offset - original_start > 0
                    || lcs_ol->position[1]->offset - latest_start > 0;

        if (is_modified || is_latest)
          {
            modified_length = modified_sync - modified_start;
            latest_length = latest_sync - latest_start;

            (*diff_ref) = apr_palloc(pool, sizeof(**diff_ref));

            (*diff_ref)->original_start = original_start - 1;
            (*diff_ref)->original_length = original_sync - original_start;
            (*diff_ref)->modified_start = modified_start - 1;
            (*diff_ref)->modified_length = modified_length;
            (*diff_ref)->latest_start = latest_start - 1;
            (*diff_ref)->latest_length = latest_length;
            (*diff_ref)->resolved_diff = NULL;

            if (is_modified && is_latest)
              {
                svn_diff__resolve_conflict(*diff_ref,
                                           &position_list[1],
                                           &position_list[2],
                                           num_tokens,
                                           pool);
              }
            else if (is_modified)
              {
                (*diff_ref)->type = svn_diff__type_diff_modified;
              }
            else
              {
                (*diff_ref)->type = svn_diff__type_diff_latest;
              }

            diff_ref = &(*diff_ref)->next;
          }

        /* Detect EOF */
        if (lcs_om->length == 0 || lcs_ol->length == 0)
            break;

        modified_length = lcs_om->length
                          - (original_sync - lcs_om->position[0]->offset);
        latest_length = lcs_ol->length
                        - (original_sync - lcs_ol->position[0]->offset);
        common_length = MIN(modified_length, latest_length);

        if (common_length > 0)
          {
            (*diff_ref) = apr_palloc(pool, sizeof(**diff_ref));

            (*diff_ref)->type = svn_diff__type_common;
            (*diff_ref)->original_start = original_sync - 1;
            (*diff_ref)->original_length = common_length;
            (*diff_ref)->modified_start = modified_sync - 1;
            (*diff_ref)->modified_length = common_length;
            (*diff_ref)->latest_start = latest_sync - 1;
            (*diff_ref)->latest_length = common_length;
            (*diff_ref)->resolved_diff = NULL;

            diff_ref = &(*diff_ref)->next;
          }

        /* Set the new offsets */
        original_start = original_sync + common_length;
        modified_start = modified_sync + common_length;
        latest_start = latest_sync + common_length;

        /* Make it easier for diff_common/conflict detection
           by recording last lcs start positions
         */
        if (position_list[1]->offset < lcs_om->position[1]->offset)
          position_list[1] = lcs_om->position[1];

        if (position_list[2]->offset < lcs_ol->position[1]->offset)
          position_list[2] = lcs_ol->position[1];

        /* Make sure we are pointing to lcs entries beyond
         * the range we just processed
         */
        while (original_start >= lcs_om->position[0]->offset + lcs_om->length
               && lcs_om->length > 0)
          {
            lcs_om = lcs_om->next;
          }

        while (original_start >= lcs_ol->position[0]->offset + lcs_ol->length
               && lcs_ol->length > 0)
          {
            lcs_ol = lcs_ol->next;
          }
      }

    *diff_ref = NULL;
  }

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}