#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
struct TYPE_7__ {scalar_t__ output_stream; scalar_t__ context_size; scalar_t__ real_output_stream; int /*<<< orphan*/ * markers; TYPE_6__* context_saver; } ;
typedef  TYPE_1__ merge_output_baton_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_8__ {scalar_t__ stream; scalar_t__ total_writes; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  flush_context_saver (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  make_trailing_context_printer (TYPE_1__*) ; 
 int /*<<< orphan*/  output_conflict_with_context_marker (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_merge_marker (TYPE_1__*,int) ; 
 int /*<<< orphan*/  output_merge_token_range (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_puts (scalar_t__,char*) ; 

__attribute__((used)) static svn_error_t *
output_conflict_with_context(void *baton,
                             apr_off_t original_start,
                             apr_off_t original_length,
                             apr_off_t modified_start,
                             apr_off_t modified_length,
                             apr_off_t latest_start,
                             apr_off_t latest_length,
                             svn_diff_t *diff)
{
  merge_output_baton_t *btn = baton;

  /* Are we currently saving starting context (as opposed to printing
     trailing context)?  If so, flush it. */
  if (btn->output_stream == btn->context_saver->stream)
    {
      if (btn->context_saver->total_writes > btn->context_size)
        SVN_ERR(svn_stream_puts(btn->real_output_stream, "@@\n"));
      SVN_ERR(flush_context_saver(btn->context_saver, btn->real_output_stream));
    }

  /* Print to the real output stream. */
  btn->output_stream = btn->real_output_stream;

  /* Output the conflict itself. */
  SVN_ERR(output_conflict_with_context_marker(btn, btn->markers[1],
                                              modified_start,
                                              modified_length));
  SVN_ERR(output_merge_token_range(btn, 1/*modified*/,
                                   modified_start, modified_length));

  SVN_ERR(output_conflict_with_context_marker(btn, btn->markers[0],
                                              original_start,
                                              original_length));
  SVN_ERR(output_merge_token_range(btn, 0/*original*/,
                                   original_start, original_length));

  SVN_ERR(output_merge_marker(btn, 2/*separator*/));
  SVN_ERR(output_merge_token_range(btn, 2/*latest*/,
                                   latest_start, latest_length));
  SVN_ERR(output_conflict_with_context_marker(btn, btn->markers[3],
                                              latest_start,
                                              latest_length));

  /* Go into print-trailing-context mode instead. */
  make_trailing_context_printer(btn);

  return SVN_NO_ERROR;
}