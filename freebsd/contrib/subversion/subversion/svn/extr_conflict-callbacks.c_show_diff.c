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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
struct TYPE_4__ {int /*<<< orphan*/  context_size; int /*<<< orphan*/  show_c_function; int /*<<< orphan*/  ignore_eol_style; } ;
typedef  TYPE_1__ svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_LOCALE_CHARSET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_cl__local_style_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_text_get_contents (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_file_diff_2 (int /*<<< orphan*/ **,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_diff_file_options_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff_file_output_unified4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 

__attribute__((used)) static svn_error_t *
show_diff(svn_client_conflict_t *conflict,
          const char *merged_abspath,
          const char *path_prefix,
          svn_cancel_func_t cancel_func,
          void *cancel_baton,
          apr_pool_t *pool)
{
  const char *path1, *path2;
  const char *label1, *label2;
  svn_diff_t *diff;
  svn_stream_t *output;
  svn_diff_file_options_t *options;
  const char *my_abspath;
  const char *their_abspath;

  SVN_ERR(svn_client_conflict_text_get_contents(NULL, &my_abspath, NULL,
                                                &their_abspath,
                                                conflict, pool, pool));
  if (merged_abspath)
    {
      /* For conflicts recorded by the 'merge' operation, show a diff between
       * 'mine' (the working version of the file as it appeared before the
       * 'merge' operation was run) and 'merged' (the version of the file
       * as it appears after the merge operation).
       *
       * For conflicts recorded by the 'update' and 'switch' operations,
       * show a diff between 'theirs' (the new pristine version of the
       * file) and 'merged' (the version of the file as it appears with
       * local changes merged with the new pristine version).
       *
       * This way, the diff is always minimal and clearly identifies changes
       * brought into the working copy by the update/switch/merge operation. */
      if (svn_client_conflict_get_operation(conflict) == svn_wc_operation_merge)
        {
          path1 = my_abspath;
          label1 = _("MINE");
        }
      else
        {
          path1 = their_abspath;
          label1 = _("THEIRS");
        }
      path2 = merged_abspath;
      label2 = _("MERGED");
    }
  else
    {
      /* There's no merged file, but we can show the
         difference between mine and theirs. */
      path1 = their_abspath;
      label1 = _("THEIRS");
      path2 = my_abspath;
      label2 = _("MINE");
    }

  label1 = apr_psprintf(pool, "%s\t- %s",
                        svn_cl__local_style_skip_ancestor(
                          path_prefix, path1, pool), label1);
  label2 = apr_psprintf(pool, "%s\t- %s",
                        svn_cl__local_style_skip_ancestor(
                          path_prefix, path2, pool), label2);

  options = svn_diff_file_options_create(pool);
  options->ignore_eol_style = TRUE;
  SVN_ERR(svn_stream_for_stdout(&output, pool));
  SVN_ERR(svn_diff_file_diff_2(&diff, path1, path2,
                               options, pool));
  return svn_diff_file_output_unified4(output, diff,
                                       path1, path2,
                                       label1, label2,
                                       APR_LOCALE_CHARSET,
                                       NULL,
                                       options->show_c_function,
                                       options->context_size,
                                       cancel_func, cancel_baton,
                                       pool);
}