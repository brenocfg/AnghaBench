#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_subst_eol_style_t ;
struct TYPE_7__ {TYPE_1__* value; } ;
typedef  TYPE_2__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  wri_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  prop_diff; int /*<<< orphan*/  old_actual_props; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_3__ merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_6__ {char const* data; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNKNOWN_EOL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 char* SVN_SUBST_NATIVE_EOL_STR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* get_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_mime_type_is_binary (char const*) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_subst_copy_and_translate4 (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (scalar_t__*,char const**,char const*) ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_translate_info (scalar_t__*,char const**,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
detranslate_wc_file(const char **detranslated_abspath,
                    const merge_target_t *mt,
                    svn_boolean_t force_copy,
                    const char *source_abspath,
                    svn_cancel_func_t cancel_func,
                    void *cancel_baton,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_boolean_t old_is_binary, new_is_binary;
  svn_subst_eol_style_t style;
  const char *eol;
  apr_hash_t *keywords;
  svn_boolean_t special;

  {
    const char *old_mime_value
      = svn_prop_get_value(mt->old_actual_props, SVN_PROP_MIME_TYPE);
    const svn_prop_t *prop = get_prop(mt->prop_diff, SVN_PROP_MIME_TYPE);
    const char *new_mime_value
      = prop ? (prop->value ? prop->value->data : NULL) : old_mime_value;

    old_is_binary = old_mime_value && svn_mime_type_is_binary(old_mime_value);
    new_is_binary = new_mime_value && svn_mime_type_is_binary(new_mime_value);
  }

  /* See what translations we want to do */
  if (old_is_binary && new_is_binary)
    {
      /* Case IV. Old and new props 'binary': detranslate keywords only */
      SVN_ERR(svn_wc__get_translate_info(NULL, NULL, &keywords, NULL,
                                         mt->db, mt->local_abspath,
                                         mt->old_actual_props, TRUE,
                                         scratch_pool, scratch_pool));
      /* ### Why override 'special'? Elsewhere it has precedence. */
      special = FALSE;
      eol = NULL;
      style = svn_subst_eol_style_none;
    }
  else if (!old_is_binary && new_is_binary)
    {
      /* Case II. Old props indicate texty, new props indicate binary:
         detranslate keywords and old eol-style */
      SVN_ERR(svn_wc__get_translate_info(&style, &eol,
                                         &keywords,
                                         &special,
                                         mt->db, mt->local_abspath,
                                         mt->old_actual_props, TRUE,
                                         scratch_pool, scratch_pool));
    }
  else
    {
      /* Case I & III. New props indicate texty, regardless of old props */

      /* In case the file used to be special, detranslate specially */
      SVN_ERR(svn_wc__get_translate_info(&style, &eol,
                                         &keywords,
                                         &special,
                                         mt->db, mt->local_abspath,
                                         mt->old_actual_props, TRUE,
                                         scratch_pool, scratch_pool));

      if (special)
        {
          keywords = NULL;
          eol = NULL;
          style = svn_subst_eol_style_none;
        }
      else
        {
          const svn_prop_t *prop;

          /* In case a new eol style was set, use that for detranslation */
          if ((prop = get_prop(mt->prop_diff, SVN_PROP_EOL_STYLE)) && prop->value)
            {
              /* Value added or changed */
              svn_subst_eol_style_from_value(&style, &eol, prop->value->data);
            }
          else if (!old_is_binary)
            {
              /* Already fetched */
            }
          else
            {
              eol = NULL;
              style = svn_subst_eol_style_none;
            }
        }
    }

  /* Now, detranslate with the settings we created above */

  if (force_copy || keywords || eol || special)
    {
      const char *temp_dir_abspath;
      const char *detranslated;

      /* Force a copy into the temporary wc area to avoid having
         temporary files created below to appear in the actual wc. */
      SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&temp_dir_abspath, mt->db,
                                             mt->wri_abspath,
                                             scratch_pool, scratch_pool));

      /* ### svn_subst_copy_and_translate4() also creates a tempfile
         ### internally.  Anyway to piggyback on that? */
      SVN_ERR(svn_io_open_unique_file3(NULL, &detranslated, temp_dir_abspath,
                                       (force_copy
                                        ? svn_io_file_del_none
                                        : svn_io_file_del_on_pool_cleanup),
                                       result_pool, scratch_pool));

      /* Always 'repair' EOLs here, so that we can apply a diff that
         changes from inconsistent newlines and no 'svn:eol-style' to
         consistent newlines and 'svn:eol-style' set.  */

      if (style == svn_subst_eol_style_native)
        eol = SVN_SUBST_NATIVE_EOL_STR;
      else if (style != svn_subst_eol_style_fixed
               && style != svn_subst_eol_style_none)
        return svn_error_create(SVN_ERR_IO_UNKNOWN_EOL, NULL, NULL);

      SVN_ERR(svn_subst_copy_and_translate4(source_abspath,
                                            detranslated,
                                            eol,
                                            TRUE /* repair */,
                                            keywords,
                                            FALSE /* contract keywords */,
                                            special,
                                            cancel_func, cancel_baton,
                                            scratch_pool));

      SVN_ERR(svn_dirent_get_absolute(detranslated_abspath, detranslated,
                                      result_pool));
    }
  else
    *detranslated_abspath = apr_pstrdup(result_pool, source_abspath);

  return SVN_NO_ERROR;
}