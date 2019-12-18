#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t svn_diff__token_index_t ;
struct TYPE_16__ {TYPE_4__* lcs; TYPE_3__** position; } ;
typedef  TYPE_2__ svn_diff__snake_t ;
struct TYPE_17__ {int offset; int token_index; struct TYPE_17__* next; } ;
typedef  TYPE_3__ svn_diff__position_t ;
struct TYPE_18__ {int refcount; struct TYPE_18__* next; TYPE_1__** position; int /*<<< orphan*/  length; } ;
typedef  TYPE_4__ svn_diff__lcs_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;
struct TYPE_15__ {int offset; } ;

/* Variables and functions */
 TYPE_4__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* prepend_lcs (TYPE_4__*,int,int,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_diff__lcs_reverse (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_diff__snake (TYPE_2__*,size_t**,TYPE_4__**,int /*<<< orphan*/ *) ; 

svn_diff__lcs_t *
svn_diff__lcs(svn_diff__position_t *position_list1, /* pointer to tail (ring) */
              svn_diff__position_t *position_list2, /* pointer to tail (ring) */
              svn_diff__token_index_t *token_counts_list1, /* array of counts */
              svn_diff__token_index_t *token_counts_list2, /* array of counts */
              svn_diff__token_index_t num_tokens,
              apr_off_t prefix_lines,
              apr_off_t suffix_lines,
              apr_pool_t *pool)
{
  apr_off_t length[2];
  svn_diff__token_index_t *token_counts[2];
  svn_diff__token_index_t unique_count[2];
  svn_diff__token_index_t token_index;
  svn_diff__snake_t *fp;
  apr_off_t d;
  apr_off_t k;
  apr_off_t p = 0;
  svn_diff__lcs_t *lcs, *lcs_freelist = NULL;

  svn_diff__position_t sentinel_position[2];

  /* Since EOF is always a sync point we tack on an EOF link
   * with sentinel positions
   */
  lcs = apr_palloc(pool, sizeof(*lcs));
  lcs->position[0] = apr_pcalloc(pool, sizeof(*lcs->position[0]));
  lcs->position[0]->offset = position_list1
                             ? position_list1->offset + suffix_lines + 1
                             : prefix_lines + suffix_lines + 1;
  lcs->position[1] = apr_pcalloc(pool, sizeof(*lcs->position[1]));
  lcs->position[1]->offset = position_list2
                             ? position_list2->offset + suffix_lines + 1
                             : prefix_lines + suffix_lines + 1;
  lcs->length = 0;
  lcs->refcount = 1;
  lcs->next = NULL;

  if (position_list1 == NULL || position_list2 == NULL)
    {
      if (suffix_lines)
        lcs = prepend_lcs(lcs, suffix_lines,
                          lcs->position[0]->offset - suffix_lines,
                          lcs->position[1]->offset - suffix_lines,
                          pool);
      if (prefix_lines)
        lcs = prepend_lcs(lcs, prefix_lines, 1, 1, pool);

      return lcs;
    }

  unique_count[1] = unique_count[0] = 0;
  for (token_index = 0; token_index < num_tokens; token_index++)
    {
      if (token_counts_list1[token_index] == 0)
        unique_count[1] += token_counts_list2[token_index];
      if (token_counts_list2[token_index] == 0)
        unique_count[0] += token_counts_list1[token_index];
    }

  /* Calculate lengths M and N of the sequences to be compared. Do not
   * count tokens unique to one file, as those are ignored in __snake.
   */
  length[0] = position_list1->offset - position_list1->next->offset + 1
              - unique_count[0];
  length[1] = position_list2->offset - position_list2->next->offset + 1
              - unique_count[1];

  /* strikerXXX: here we allocate the furthest point array, which is
   * strikerXXX: sized M + N + 3 (!)
   */
  fp = apr_pcalloc(pool,
                   sizeof(*fp) * (apr_size_t)(length[0] + length[1] + 3));

  /* The origo of fp corresponds to the end state, where we are
   * at the end of both files. The valid states thus span from
   * -N (at end of first file and at the beginning of the second
   * file) to +M (the opposite :). Finally, svn_diff__snake needs
   * 1 extra slot on each side to work.
   */
  fp += length[1] + 1;

  sentinel_position[0].next = position_list1->next;
  position_list1->next = &sentinel_position[0];
  sentinel_position[0].offset = position_list1->offset + 1;
  token_counts[0] = token_counts_list1;

  sentinel_position[1].next = position_list2->next;
  position_list2->next = &sentinel_position[1];
  sentinel_position[1].offset = position_list2->offset + 1;
  token_counts[1] = token_counts_list2;

  /* Negative indices will not be used elsewhere
   */
  sentinel_position[0].token_index = -1;
  sentinel_position[1].token_index = -2;

  /* position d = M - N corresponds to the initial state, where
   * we are at the beginning of both files.
   */
  d = length[0] - length[1];

  /* k = d - 1 will be the first to be used to get previous
   * position information from, make sure it holds sane
   * data
   */
  fp[d - 1].position[0] = sentinel_position[0].next;
  fp[d - 1].position[1] = &sentinel_position[1];

  p = 0;
  do
    {
      /* For k < 0, insertions are free */
      for (k = (d < 0 ? d : 0) - p; k < 0; k++)
        {
          svn_diff__snake(fp + k, token_counts, &lcs_freelist, pool);
        }
      /* for k > 0, deletions are free */
      for (k = (d > 0 ? d : 0) + p; k >= 0; k--)
        {
          svn_diff__snake(fp + k, token_counts, &lcs_freelist, pool);
        }

      p++;
    }
  while (fp[0].position[1] != &sentinel_position[1]);

  if (suffix_lines)
    lcs->next = prepend_lcs(fp[0].lcs, suffix_lines,
                            lcs->position[0]->offset - suffix_lines,
                            lcs->position[1]->offset - suffix_lines,
                            pool);
  else
    lcs->next = fp[0].lcs;

  lcs = svn_diff__lcs_reverse(lcs);

  position_list1->next = sentinel_position[0].next;
  position_list2->next = sentinel_position[1].next;

  if (prefix_lines)
    return prepend_lcs(lcs, prefix_lines, 1, 1, pool);
  else
    return lcs;
}