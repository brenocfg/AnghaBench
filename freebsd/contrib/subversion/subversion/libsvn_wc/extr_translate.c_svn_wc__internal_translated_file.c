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
typedef  scalar_t__ svn_subst_eol_style_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNKNOWN_EOL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_SUBST_NATIVE_EOL_STR ; 
 int SVN_WC_TRANSLATE_FORCE_COPY ; 
 int SVN_WC_TRANSLATE_FORCE_EOL_REPAIR ; 
 int SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 int SVN_WC_TRANSLATE_USE_GLOBAL_TMP ; 
 int TRUE ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_copy_and_translate4 (char const*,char const*,char const*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 
 int /*<<< orphan*/  svn_subst_translation_required (scalar_t__,char const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_translate_info (scalar_t__*,char const**,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_translated_file(const char **xlated_abspath,
                                 const char *src_abspath,
                                 svn_wc__db_t *db,
                                 const char *versioned_abspath,
                                 apr_uint32_t flags,
                                 svn_cancel_func_t cancel_func,
                                 void *cancel_baton,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  svn_subst_eol_style_t style;
  const char *eol;
  apr_hash_t *keywords;
  svn_boolean_t special;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(src_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(versioned_abspath));
  SVN_ERR(svn_wc__get_translate_info(&style, &eol,
                                     &keywords,
                                     &special,
                                     db, versioned_abspath, NULL, FALSE,
                                     scratch_pool, scratch_pool));

  if (! svn_subst_translation_required(style, eol, keywords, special, TRUE)
      && (! (flags & SVN_WC_TRANSLATE_FORCE_COPY)))
    {
      /* Translation would be a no-op, so return the original file. */
      *xlated_abspath = src_abspath;
    }
  else  /* some translation (or copying) is necessary */
    {
      const char *tmp_dir;
      const char *tmp_vfile;
      svn_boolean_t repair_forced
          = (flags & SVN_WC_TRANSLATE_FORCE_EOL_REPAIR) != 0;
      svn_boolean_t expand = (flags & SVN_WC_TRANSLATE_TO_NF) == 0;

      if (flags & SVN_WC_TRANSLATE_USE_GLOBAL_TMP)
        tmp_dir = NULL;
      else
        SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tmp_dir, db, versioned_abspath,
                                               scratch_pool, scratch_pool));

      SVN_ERR(svn_io_open_unique_file3(NULL, &tmp_vfile, tmp_dir,
                (flags & SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP)
                  ? svn_io_file_del_none
                  : svn_io_file_del_on_pool_cleanup,
                result_pool, scratch_pool));

      /* ### ugh. the repair behavior does NOT match the docstring. bleah.
         ### all of these translation functions are crap and should go
         ### away anyways. we'll just deprecate most of the functions and
         ### properly document the survivors */

      if (expand)
        {
          /* from normal form */

          repair_forced = TRUE;
        }
      else
        {
          /* to normal form */

          if (style == svn_subst_eol_style_native)
            eol = SVN_SUBST_NATIVE_EOL_STR;
          else if (style == svn_subst_eol_style_fixed)
            repair_forced = TRUE;
          else if (style != svn_subst_eol_style_none)
            return svn_error_create(SVN_ERR_IO_UNKNOWN_EOL, NULL, NULL);
        }

      SVN_ERR(svn_subst_copy_and_translate4(src_abspath, tmp_vfile,
                                            eol, repair_forced,
                                            keywords,
                                            expand,
                                            special,
                                            cancel_func, cancel_baton,
                                            result_pool));

      *xlated_abspath = tmp_vfile;
    }

  return SVN_NO_ERROR;
}