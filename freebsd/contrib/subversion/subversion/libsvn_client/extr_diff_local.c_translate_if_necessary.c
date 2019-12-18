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
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STRINGIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_subst_eol_style_none ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_translation_required (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
translate_if_necessary(const char **local_abspath,
                       apr_hash_t *props,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  const svn_string_t *eol_style_val;
  const svn_string_t *keywords_val;
  svn_subst_eol_style_t eol_style;
  const char *eol;
  apr_hash_t *keywords;
  svn_stream_t *contents;
  svn_stream_t *dst;

  /* if (svn_hash_gets(props, SVN_PROP_SPECIAL))
      ### TODO: Implement */

  eol_style_val = svn_hash_gets(props, SVN_PROP_EOL_STYLE);
  keywords_val = svn_hash_gets(props, SVN_PROP_KEYWORDS);

  if (eol_style_val)
    svn_subst_eol_style_from_value(&eol_style, &eol, eol_style_val->data);
  else
    {
      eol = NULL;
      eol_style = svn_subst_eol_style_none;
    }

  if (keywords_val)
    SVN_ERR(svn_subst_build_keywords3(&keywords, keywords_val->data,
                                      APR_STRINGIFY(SVN_INVALID_REVNUM),
                                      "", "", 0, "", scratch_pool));
  else
    keywords = NULL;

  if (!svn_subst_translation_required(eol_style, eol, keywords, FALSE, FALSE))
    return SVN_NO_ERROR;

  SVN_ERR(svn_stream_open_readonly(&contents, *local_abspath,
                                    scratch_pool, scratch_pool));

  SVN_ERR(svn_stream_open_unique(&dst, local_abspath, NULL,
                                  svn_io_file_del_on_pool_cleanup,
                                  result_pool, scratch_pool));

  dst = svn_subst_stream_translated(dst, eol, TRUE /* repair */,
                                    keywords, FALSE /* expand */,
                                    scratch_pool);

  SVN_ERR(svn_stream_copy3(contents, dst, cancel_func, cancel_baton,
                           scratch_pool));

  return SVN_NO_ERROR;
}