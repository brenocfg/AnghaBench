#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_9__ {scalar_t__ number; } ;
struct TYPE_10__ {TYPE_1__ value; void* kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
struct TYPE_11__ {scalar_t__ revision; } ;
typedef  TYPE_3__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_client_diff_peg6 (int /*<<< orphan*/ *,char const*,TYPE_2__ const*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_output_encoding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cstring_split (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_opt_revision_number ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
display_diff(const svn_log_entry_t *log_entry,
             const char *target_path_or_url,
             const svn_opt_revision_t *target_peg_revision,
             svn_depth_t depth,
             const char *diff_extensions,
             svn_stream_t *outstream,
             svn_stream_t *errstream,
             svn_client_ctx_t *ctx,
             apr_pool_t *pool)
{
  apr_array_header_t *diff_options;
  svn_opt_revision_t start_revision;
  svn_opt_revision_t end_revision;

  /* Fall back to "" to get options initialized either way. */
  if (diff_extensions)
    diff_options = svn_cstring_split(diff_extensions, " \t\n\r",
                                     TRUE, pool);
  else
    diff_options = NULL;

  start_revision.kind = svn_opt_revision_number;
  start_revision.value.number = log_entry->revision - 1;
  end_revision.kind = svn_opt_revision_number;
  end_revision.value.number = log_entry->revision;

  SVN_ERR(svn_stream_puts(outstream, "\n"));
  SVN_ERR(svn_client_diff_peg6(diff_options,
                               target_path_or_url,
                               target_peg_revision,
                               &start_revision, &end_revision,
                               NULL,
                               depth,
                               FALSE /* ignore ancestry */,
                               FALSE /* no diff added */,
                               TRUE  /* no diff deleted */,
                               FALSE /* show copies as adds */,
                               FALSE /* ignore content type */,
                               FALSE /* ignore prop diff */,
                               FALSE /* properties only */,
                               FALSE /* use git diff format */,
                               svn_cmdline_output_encoding(pool),
                               outstream,
                               errstream,
                               NULL,
                               ctx, pool));
  SVN_ERR(svn_stream_puts(outstream, _("\n")));
  return SVN_NO_ERROR;
}