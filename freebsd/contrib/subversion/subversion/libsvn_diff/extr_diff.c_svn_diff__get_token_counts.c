#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_diff__token_index_t ;
struct TYPE_3__ {size_t token_index; struct TYPE_3__* next; } ;
typedef  TYPE_1__ svn_diff__position_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_diff__token_index_t*
svn_diff__get_token_counts(svn_diff__position_t *loop_start,
                           svn_diff__token_index_t num_tokens,
                           apr_pool_t *pool)
{
  svn_diff__token_index_t *token_counts;
  svn_diff__token_index_t token_index;
  svn_diff__position_t *current;

  token_counts = apr_palloc(pool, num_tokens * sizeof(*token_counts));
  for (token_index = 0; token_index < num_tokens; token_index++)
    token_counts[token_index] = 0;

  current = loop_start;
  if (current != NULL)
    {
      do
        {
          token_counts[current->token_index]++;
          current = current->next;
        }
      while (current != loop_start);
    }

  return token_counts;
}