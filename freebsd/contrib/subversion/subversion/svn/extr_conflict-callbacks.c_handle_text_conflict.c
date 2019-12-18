#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_2__ svn_cmdline_prompt_baton_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  svn_cl__conflict_stats_t ;
typedef  int svn_boolean_t ;
struct TYPE_16__ {scalar_t__ choice; int /*<<< orphan*/  code; } ;
typedef  TYPE_3__ client_option_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL ; 
 scalar_t__ SVN_ERR_EXTERNAL_PROGRAM ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  build_text_conflict_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help_string (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_conflict_resolved (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_editor (int*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prompt_user (TYPE_3__ const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_conflicts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_diff (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* svn_cl__local_style_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cl__merge_file (int*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cl__merge_file_externally (char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_incoming_text_where_conflicted ; 
 scalar_t__ svn_client_conflict_option_merged_text ; 
 scalar_t__ svn_client_conflict_option_postpone ; 
 scalar_t__ svn_client_conflict_option_undefined ; 
 scalar_t__ svn_client_conflict_option_unspecified ; 
 scalar_t__ svn_client_conflict_option_working_text_where_conflicted ; 
 int /*<<< orphan*/  svn_client_conflict_text_get_contents (int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_client_conflict_text_get_mime_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 char* svn_err_best_message (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int svn_mime_type_is_binary (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_text_conflict(svn_boolean_t *resolved,
                     svn_boolean_t *postponed,
                     svn_boolean_t *quit,
                     svn_boolean_t *printed_description,
                     svn_client_conflict_t *conflict,
                     const char *path_prefix,
                     svn_cmdline_prompt_baton_t *pb,
                     const char *editor_cmd,
                     apr_hash_t *config,
                     svn_cl__conflict_stats_t *conflict_stats,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_boolean_t diff_allowed = FALSE;
  /* Have they done something that might have affected the merged file? */
  svn_boolean_t performed_edit = FALSE;
  /* Have they done *something* (edit, look at diff, etc) to
     give them a rational basis for choosing (r)esolved? */
  svn_boolean_t knows_something = FALSE;
  const char *local_relpath;
  const char *local_abspath = svn_client_conflict_get_local_abspath(conflict);
  const char *mime_type = svn_client_conflict_text_get_mime_type(conflict);
  svn_boolean_t is_binary = mime_type ? svn_mime_type_is_binary(mime_type)
                                      : FALSE;
  const char *base_abspath;
  const char *my_abspath;
  const char *their_abspath;
  const char *merged_abspath = svn_client_conflict_get_local_abspath(conflict);
  apr_array_header_t *text_conflict_options;
  svn_client_conflict_option_id_t option_id; 

  option_id = svn_client_conflict_option_unspecified;

  SVN_ERR(svn_client_conflict_text_get_contents(NULL, &my_abspath,
                                                &base_abspath, &their_abspath,
                                                conflict, scratch_pool,
                                                scratch_pool));

  local_relpath = svn_cl__local_style_skip_ancestor(path_prefix,
                                                    local_abspath,
                                                    scratch_pool);

  if (!*printed_description)
    {
      if (is_binary)
        SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                                    _("Merge conflict discovered in binary "
                                      "file '%s'.\n"),
                                    local_relpath));
      else
        SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                                    _("Merge conflict discovered in file '%s'.\n"),
                                    local_relpath));
      *printed_description = TRUE;
    }

  /* ### TODO This whole feature availability check is grossly outdated.
     DIFF_ALLOWED needs either to be redefined or to go away.
   */

  /* Diffing can happen between base and merged, to show conflict
     markers to the user (this is the typical 3-way merge
     scenario), or if no base is available, we can show a diff
     between mine and theirs. */
  if (!is_binary &&
      ((merged_abspath && base_abspath)
      || (!base_abspath && my_abspath && their_abspath)))
    diff_allowed = TRUE;

  SVN_ERR(build_text_conflict_options(&text_conflict_options, conflict, ctx,
                                      is_binary, scratch_pool, scratch_pool));
  while (TRUE)
    {
      const char *suggested_options[9]; /* filled statically below */
      const char **next_option = suggested_options;
      const client_option_t *opt;

      svn_pool_clear(iterpool);

      *next_option++ = "p";
      if (diff_allowed)
        {
          /* We need one more path for this feature. */
          if (my_abspath)
            *next_option++ = "df";

          *next_option++ = "e";

          /* We need one more path for this feature. */
          if (my_abspath)
            *next_option++ = "m";

          if (knows_something)
            *next_option++ = "r";
        }
      else
        {
          if (knows_something || is_binary)
            *next_option++ = "r";

          /* The 'mine-full' option selects the ".mine" file for texts or
           * the current working directory file for binary files. */
          if (my_abspath || is_binary)
            *next_option++ = "mf";

          *next_option++ = "tf";
        }
      *next_option++ = "s";
      *next_option++ = NULL;

      SVN_ERR(prompt_user(&opt, text_conflict_options, suggested_options,
                          NULL, pb, iterpool));
      if (! opt)
        continue;

      if (strcmp(opt->code, "q") == 0)
        {
          option_id = opt->choice;
          *quit = TRUE;
          break;
        }
      else if (strcmp(opt->code, "s") == 0)
        {
          const char *helpstr;

          SVN_ERR(help_string(&helpstr, text_conflict_options, iterpool));
          SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "\n%s\n",
                                      helpstr));
        }
      else if (strcmp(opt->code, "dc") == 0)
        {
          if (is_binary)
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                                          _("Invalid option; cannot "
                                            "display conflicts for a "
                                            "binary file.\n\n")));
              continue;
            }
          else if (! (my_abspath && base_abspath && their_abspath))
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                                          _("Invalid option; original "
                                            "files not available.\n\n")));
              continue;
            }
          SVN_ERR(show_conflicts(conflict,
                                 pb->cancel_func,
                                 pb->cancel_baton,
                                 iterpool));
          knows_something = TRUE;
        }
      else if (strcmp(opt->code, "df") == 0)
        {
          /* Re-check preconditions. */
          if (! diff_allowed || ! my_abspath)
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                             _("Invalid option; there's no "
                                "merged version to diff.\n\n")));
              continue;
            }

          SVN_ERR(show_diff(conflict, merged_abspath, path_prefix,
                            pb->cancel_func, pb->cancel_baton,
                            iterpool));
          knows_something = TRUE;
        }
      else if (strcmp(opt->code, "e") == 0 || strcmp(opt->code, ":-E") == 0)
        {
          SVN_ERR(open_editor(&performed_edit, merged_abspath, editor_cmd,
                              config, iterpool));
          if (performed_edit)
            knows_something = TRUE;
        }
      else if (strcmp(opt->code, "m") == 0 || strcmp(opt->code, ":-g") == 0 ||
               strcmp(opt->code, "=>-") == 0 || strcmp(opt->code, ":>.") == 0)
        {
          svn_error_t *err;

          /* Re-check preconditions. */
          if (! my_abspath)
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                             _("Invalid option; there's no "
                                "base path to merge.\n\n")));
              continue;
            }

          err = svn_cl__merge_file_externally(base_abspath,
                                              their_abspath,
                                              my_abspath,
                                              merged_abspath,
                                              local_abspath, config,
                                              NULL, iterpool);
          if (err)
            {
              if (err->apr_err == SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL)
                {
                  svn_boolean_t remains_in_conflict = TRUE;

                  /* Try the internal merge tool. */
                  svn_error_clear(err);
                  SVN_ERR(svn_cl__merge_file(&remains_in_conflict,
                                             base_abspath,
                                             their_abspath,
                                             my_abspath,
                                             merged_abspath,
                                             local_abspath,
                                             path_prefix,
                                             editor_cmd,
                                             config,
                                             pb->cancel_func,
                                             pb->cancel_baton,
                                             iterpool));
                  knows_something = !remains_in_conflict;
                }
              else if (err->apr_err == SVN_ERR_EXTERNAL_PROGRAM)
                {
                  char buf[1024];
                  const char *message;

                  message = svn_err_best_message(err, buf, sizeof(buf));
                  SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                                              "%s\n", message));
                  svn_error_clear(err);
                  continue;
                }
              else
                return svn_error_trace(err);
            }
          else
            {
              /* The external merge tool's exit code was either 0 or 1.
               * The tool may leave the file conflicted by exiting with
               * exit code 1, and we allow the user to mark the conflict
               * resolved in this case. */
              performed_edit = TRUE;
              knows_something = TRUE;
            }
        }
      else if (strcmp(opt->code, "l") == 0 || strcmp(opt->code, ":-l") == 0)
        {
          /* ### This check should be earlier as it's nasty to offer an option
           *     and then when the user chooses it say 'Invalid option'. */
          /* ### 'merged_abspath' shouldn't be necessary *before* we launch the
           *     resolver: it should be the *result* of doing so. */
          if (base_abspath && their_abspath && my_abspath && merged_abspath)
            {
              svn_error_t *err;
              char buf[1024];
              const char *message;

              err = svn_cl__merge_file_externally(base_abspath,
                                                  their_abspath,
                                                  my_abspath,
                                                  merged_abspath,
                                                  local_abspath,
                                                  config, NULL, iterpool);
              if (err && (err->apr_err == SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL ||
                          err->apr_err == SVN_ERR_EXTERNAL_PROGRAM))
                {
                  message = svn_err_best_message(err, buf, sizeof(buf));
                  SVN_ERR(svn_cmdline_fprintf(stderr, iterpool, "%s\n",
                                              message));
                  svn_error_clear(err);
                }
              else if (err)
                return svn_error_trace(err);
              else
                performed_edit = TRUE;

              if (performed_edit)
                knows_something = TRUE;
            }
          else
            SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                                        _("Invalid option.\n\n")));
        }
      else if (strcmp(opt->code, "i") == 0)
        {
          svn_boolean_t remains_in_conflict = TRUE;

          SVN_ERR(svn_cl__merge_file(&remains_in_conflict,
                                     base_abspath,
                                     their_abspath,
                                     my_abspath,
                                     merged_abspath,
                                     local_abspath,
                                     path_prefix,
                                     editor_cmd,
                                     config,
                                     pb->cancel_func,
                                     pb->cancel_baton,
                                     iterpool));

          if (!remains_in_conflict)
            knows_something = TRUE;
        }
      else if (opt->choice != svn_client_conflict_option_undefined)
        {
          if ((opt->choice == svn_client_conflict_option_working_text_where_conflicted
               || opt->choice == svn_client_conflict_option_incoming_text_where_conflicted)
              && is_binary)
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                                          _("Invalid option; cannot choose "
                                            "based on conflicts in a "
                                            "binary file.\n\n")));
              continue;
            }

          /* We only allow the user accept the merged version of
             the file if they've edited it, or at least looked at
             the diff. */
          if (opt->choice == svn_client_conflict_option_merged_text
              && ! knows_something && diff_allowed)
            {
              SVN_ERR(svn_cmdline_fprintf(
                        stderr, iterpool,
                        _("Invalid option; use diff/edit/merge/launch "
                          "before choosing 'mark resolved'.\n\n")));
              continue;
            }

          option_id = opt->choice;
          break;
        }
    }
  svn_pool_destroy(iterpool);

  if (option_id != svn_client_conflict_option_unspecified &&
      option_id != svn_client_conflict_option_postpone)
    {
      SVN_ERR(mark_conflict_resolved(conflict, option_id,
                                     TRUE, NULL, FALSE,
                                     path_prefix, conflict_stats,
                                     ctx, scratch_pool));
      *resolved = TRUE;
    }
  else
    {
      *resolved = FALSE;
      *postponed = (option_id == svn_client_conflict_option_postpone);
    }

  return SVN_NO_ERROR;
}