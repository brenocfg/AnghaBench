#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ svn_cmdline_prompt_baton_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int svn_boolean_t ;
struct TYPE_8__ {scalar_t__ choice; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ client_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  build_prop_conflict_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edit_prop_conflict (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prompt_user (TYPE_2__ const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_prop_conflict (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_cl__local_style_skip_ancestor (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client_conflict_option_find_by_id (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ svn_client_conflict_option_merged_text ; 
 int /*<<< orphan*/  svn_client_conflict_option_set_merged_propval (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ svn_client_conflict_option_undefined ; 
 int /*<<< orphan*/  svn_client_conflict_prop_get_description (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_prop_get_propvals (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_prop_get_resolution_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_one_prop_conflict(svn_client_conflict_option_t **option,
                         svn_boolean_t *quit,
                         const char *path_prefix,
                         svn_cmdline_prompt_baton_t *pb,
                         const char *editor_cmd,
                         apr_hash_t *config,
                         svn_client_conflict_t *conflict,
                         const char *propname,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  const char *description;
  const svn_string_t *merged_propval = NULL;
  svn_boolean_t resolved_allowed = FALSE;
  const svn_string_t *base_propval;
  const svn_string_t *my_propval;
  const svn_string_t *their_propval;
  apr_array_header_t *resolution_options;
  apr_array_header_t *prop_conflict_options;

  SVN_ERR(svn_client_conflict_prop_get_propvals(NULL, &my_propval,
                                                &base_propval, &their_propval,
                                                conflict, propname,
                                                scratch_pool));

  SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                              _("Conflict for property '%s' discovered"
                                " on '%s'.\n"),
                              propname,
                              svn_cl__local_style_skip_ancestor(
                                path_prefix,
                                svn_client_conflict_get_local_abspath(conflict),
                                scratch_pool)));
  SVN_ERR(svn_client_conflict_prop_get_description(&description, conflict,
                                                   scratch_pool, scratch_pool));
  SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "%s\n", description));

  SVN_ERR(svn_client_conflict_prop_get_resolution_options(&resolution_options,
                                                          conflict, ctx,
                                                          result_pool,
                                                          scratch_pool));
  SVN_ERR(build_prop_conflict_options(&prop_conflict_options, conflict, ctx,
                                      scratch_pool, scratch_pool));
  iterpool = svn_pool_create(scratch_pool);
  while (TRUE)
    {
      const client_option_t *opt;
      const char *suggested_options[9]; /* filled statically below */
      const char **next_option = suggested_options;

      *next_option++ = "p";
      *next_option++ = "mf";
      *next_option++ = "tf";
      *next_option++ = "dc";
      *next_option++ = "e";
      if (resolved_allowed)
        *next_option++ = "r";
      *next_option++ = "q";
      *next_option++ = "h";
      *next_option++ = NULL;

      svn_pool_clear(iterpool);

      SVN_ERR(prompt_user(&opt, prop_conflict_options, suggested_options,
                          NULL, pb, iterpool));
      if (! opt)
        continue;

      if (strcmp(opt->code, "q") == 0)
        {
          *option = svn_client_conflict_option_find_by_id(resolution_options,
                                                          opt->choice);
          *quit = TRUE;
          break;
        }
      else if (strcmp(opt->code, "dc") == 0)
        {
          SVN_ERR(show_prop_conflict(base_propval, my_propval, their_propval,
                                     merged_propval,
                                     pb->cancel_func, pb->cancel_baton,
                                     scratch_pool));
        }
      else if (strcmp(opt->code, "e") == 0)
        {
          SVN_ERR(edit_prop_conflict(&merged_propval,
                                     base_propval, my_propval, their_propval,
                                     editor_cmd, config, pb,
                                     result_pool, scratch_pool));
          resolved_allowed = (merged_propval != NULL);
        }
      else if (strcmp(opt->code, "r") == 0)
        {
          if (! resolved_allowed)
            {
              SVN_ERR(svn_cmdline_fprintf(stderr, iterpool,
                             _("Invalid option; please edit the property "
                               "first.\n\n")));
              continue;
            }

          *option = svn_client_conflict_option_find_by_id(
                      resolution_options,
                      svn_client_conflict_option_merged_text);
          svn_client_conflict_option_set_merged_propval(*option,
                                                        merged_propval);
          break;
        }
      else if (opt->choice != svn_client_conflict_option_undefined)
        {
          *option = svn_client_conflict_option_find_by_id(resolution_options,
                                                          opt->choice);
          break;
        }
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}