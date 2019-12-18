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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_subst_eol_style_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNKNOWN_EOL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 char* SVN_SUBST_NATIVE_EOL_STR ; 
 int /*<<< orphan*/  properties_same_p (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_contents_same2 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (scalar_t__*,char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 
 int /*<<< orphan*/  svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
files_same_p(svn_boolean_t *same,
             const char *older_abspath,
             apr_hash_t *original_props,
             const char *mine_abspath,
             svn_wc_context_t *wc_ctx,
             apr_pool_t *scratch_pool)
{
  apr_hash_t *working_props;

  SVN_ERR(svn_wc_prop_list2(&working_props, wc_ctx, mine_abspath,
                            scratch_pool, scratch_pool));

  /* Compare the properties */
  SVN_ERR(properties_same_p(same, original_props, working_props,
                            scratch_pool));
  if (*same)
    {
      svn_stream_t *mine_stream;
      svn_stream_t *older_stream;
      svn_string_t *special = svn_hash_gets(working_props, SVN_PROP_SPECIAL);
      svn_string_t *eol_style = svn_hash_gets(working_props, SVN_PROP_EOL_STYLE);
      svn_string_t *keywords = svn_hash_gets(working_props, SVN_PROP_KEYWORDS);

      /* Compare the file content, translating 'mine' to 'normal' form. */
      if (special != NULL)
        SVN_ERR(svn_subst_read_specialfile(&mine_stream, mine_abspath,
                                           scratch_pool, scratch_pool));
      else
        SVN_ERR(svn_stream_open_readonly(&mine_stream, mine_abspath,
                                         scratch_pool, scratch_pool));

      if (!special && (eol_style || keywords))
        {
          apr_hash_t *kw = NULL;
          const char *eol = NULL;
          svn_subst_eol_style_t style;

          /* We used to use svn_client__get_normalized_stream() here, but
             that doesn't work in 100% of the cases because it doesn't
             convert EOLs to the repository form; just to '\n'.
           */

          if (eol_style)
            {
              svn_subst_eol_style_from_value(&style, &eol, eol_style->data);

              if (style == svn_subst_eol_style_native)
                eol = SVN_SUBST_NATIVE_EOL_STR;
              else if (style != svn_subst_eol_style_fixed
                       && style != svn_subst_eol_style_none)
                return svn_error_create(SVN_ERR_IO_UNKNOWN_EOL, NULL, NULL);
            }

          if (keywords)
            SVN_ERR(svn_subst_build_keywords3(&kw, keywords->data, "", "",
                                              "", 0, "", scratch_pool));

          mine_stream = svn_subst_stream_translated(
            mine_stream, eol, FALSE, kw, FALSE, scratch_pool);
        }

      SVN_ERR(svn_stream_open_readonly(&older_stream, older_abspath,
                                       scratch_pool, scratch_pool));

      SVN_ERR(svn_stream_contents_same2(same, mine_stream, older_stream,
                                        scratch_pool));

    }

  return SVN_NO_ERROR;
}