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
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_4__ {scalar_t__ context_size; scalar_t__* hunk_length; scalar_t__* hunk_start; scalar_t__* current_token; int /*<<< orphan*/  hunk_delimiter; } ;
typedef  TYPE_1__ output_baton_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  output_unified_flush_hunk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_unified_token_range (TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unified_output_context ; 
 int /*<<< orphan*/  unified_output_delete ; 
 int /*<<< orphan*/  unified_output_insert ; 
 int /*<<< orphan*/  unified_output_skip ; 

__attribute__((used)) static svn_error_t *
output_unified_diff_modified(void *baton,
                             apr_off_t original_start,
                             apr_off_t original_length,
                             apr_off_t modified_start,
                             apr_off_t modified_length,
                             apr_off_t latest_start,
                             apr_off_t latest_length)
{
  output_baton_t *output_baton = baton;
  apr_off_t context_prefix_length;
  apr_off_t prev_context_end;
  svn_boolean_t init_hunk = FALSE;

  if (original_start > output_baton->context_size)
    context_prefix_length = output_baton->context_size;
  else
    context_prefix_length = original_start;

  /* Calculate where the previous hunk will end if we would write it now
     (including the necessary context at the end) */
  if (output_baton->hunk_length[0] > 0 || output_baton->hunk_length[1] > 0)
    {
      prev_context_end = output_baton->hunk_start[0]
                         + output_baton->hunk_length[0]
                         + output_baton->context_size;
    }
  else
    {
      prev_context_end = -1;

      if (output_baton->hunk_start[0] == 0
          && (original_length > 0 || modified_length > 0))
        init_hunk = TRUE;
    }

  /* If the changed range is far enough from the previous range, flush the current
     hunk. */
  {
    apr_off_t new_hunk_start = (original_start - context_prefix_length);

    if (output_baton->current_token[0] < new_hunk_start
          && prev_context_end <= new_hunk_start)
      {
        SVN_ERR(output_unified_flush_hunk(output_baton,
                                          output_baton->hunk_delimiter));
        init_hunk = TRUE;
      }
    else if (output_baton->hunk_length[0] > 0
             || output_baton->hunk_length[1] > 0)
      {
        /* We extend the current hunk */

        /* Original: Output the context preceding the changed range */
        SVN_ERR(output_unified_token_range(output_baton, 0 /* original */,
                                           unified_output_context,
                                           original_start));
      }
  }

  /* Original: Skip lines until we are at the beginning of the context we want
     to display */
  SVN_ERR(output_unified_token_range(output_baton, 0 /* original */,
                                     unified_output_skip,
                                     original_start - context_prefix_length));

  if (init_hunk)
    {
      SVN_ERR_ASSERT(output_baton->hunk_length[0] == 0
                     && output_baton->hunk_length[1] == 0);

      output_baton->hunk_start[0] = original_start - context_prefix_length;
      output_baton->hunk_start[1] = modified_start - context_prefix_length;
    }

  /* Modified: Skip lines until we are at the start of the changed range */
  SVN_ERR(output_unified_token_range(output_baton, 1 /* modified */,
                                     unified_output_skip,
                                     modified_start));

  /* Original: Output the context preceding the changed range */
  SVN_ERR(output_unified_token_range(output_baton, 0 /* original */,
                                    unified_output_context,
                                    original_start));

  /* Both: Output the changed range */
  SVN_ERR(output_unified_token_range(output_baton, 0 /* original */,
                                     unified_output_delete,
                                     original_start + original_length));
  SVN_ERR(output_unified_token_range(output_baton, 1 /* modified */,
                                     unified_output_insert,
                                     modified_start + modified_length));

  return SVN_NO_ERROR;
}