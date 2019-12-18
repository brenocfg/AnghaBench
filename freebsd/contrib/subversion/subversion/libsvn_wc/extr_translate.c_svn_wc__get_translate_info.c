#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,char const*) ; 
 int /*<<< orphan*/  svn_wc__expand_keywords (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_actual_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__get_translate_info(svn_subst_eol_style_t *style,
                           const char **eol,
                           apr_hash_t **keywords,
                           svn_boolean_t *special,
                           svn_wc__db_t *db,
                           const char *local_abspath,
                           apr_hash_t *props,
                           svn_boolean_t for_normalization,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const char *propval;
  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  if (props == NULL)
    SVN_ERR(svn_wc__get_actual_props(&props, db, local_abspath,
                                     scratch_pool, scratch_pool));

  if (eol)
    {
      propval = svn_prop_get_value(props, SVN_PROP_EOL_STYLE);

      svn_subst_eol_style_from_value(style, eol, propval);
    }

  if (keywords)
    {
      propval = svn_prop_get_value(props, SVN_PROP_KEYWORDS);

      if (!propval || *propval == '\0')
        *keywords = NULL;
      else
        SVN_ERR(svn_wc__expand_keywords(keywords,
                                        db, local_abspath, NULL,
                                        propval, for_normalization,
                                        result_pool, scratch_pool));
    }
  if (special)
    {
      propval = svn_prop_get_value(props, SVN_PROP_SPECIAL);

      *special = (propval != NULL);
    }

  return SVN_NO_ERROR;
}