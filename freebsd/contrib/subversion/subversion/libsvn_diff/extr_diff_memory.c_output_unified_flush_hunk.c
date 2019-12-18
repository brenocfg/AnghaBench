#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {TYPE_2__* hunk; scalar_t__* hunk_start; scalar_t__* hunk_length; int /*<<< orphan*/  output_stream; int /*<<< orphan*/  pool; int /*<<< orphan*/  header_encoding; scalar_t__ context_size; } ;
typedef  TYPE_1__ output_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  output_unified_token_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_diff__unified_write_hunk_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_stringbuf_isempty (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_2__*) ; 
 int /*<<< orphan*/  unified_output_context ; 

__attribute__((used)) static svn_error_t *
output_unified_flush_hunk(output_baton_t *baton,
                          const char *hunk_delimiter)
{
  apr_off_t target_token;
  apr_size_t hunk_len;
  apr_off_t old_start;
  apr_off_t new_start;

  if (svn_stringbuf_isempty(baton->hunk))
    return SVN_NO_ERROR;

  svn_pool_clear(baton->pool);

  /* Write the trailing context */
  target_token = baton->hunk_start[0] + baton->hunk_length[0]
                 + baton->context_size;
  SVN_ERR(output_unified_token_range(baton, 0 /*original*/,
                                     unified_output_context,
                                     target_token));
  if (hunk_delimiter == NULL)
    hunk_delimiter = "@@";

  old_start = baton->hunk_start[0];
  new_start = baton->hunk_start[1];

  /* If the file is non-empty, convert the line indexes from
     zero based to one based */
  if (baton->hunk_length[0])
    old_start++;
  if (baton->hunk_length[1])
    new_start++;

  /* Write the hunk header */
  SVN_ERR(svn_diff__unified_write_hunk_header(
            baton->output_stream, baton->header_encoding, hunk_delimiter,
            old_start, baton->hunk_length[0],
            new_start, baton->hunk_length[1],
            NULL /* hunk_extra_context */,
            baton->pool));

  hunk_len = baton->hunk->len;
  SVN_ERR(svn_stream_write(baton->output_stream,
                           baton->hunk->data, &hunk_len));

  /* Prepare for the next hunk */
  baton->hunk_length[0] = 0;
  baton->hunk_length[1] = 0;
  baton->hunk_start[0] = 0;
  baton->hunk_start[1] = 0;
  svn_stringbuf_setempty(baton->hunk);

  return SVN_NO_ERROR;
}