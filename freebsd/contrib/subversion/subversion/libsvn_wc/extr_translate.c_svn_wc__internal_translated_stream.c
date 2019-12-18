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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNKNOWN_EOL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_SUBST_NATIVE_EOL_STR ; 
 int SVN_WC_TRANSLATE_FORCE_EOL_REPAIR ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 int TRUE ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_create_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 scalar_t__ svn_subst_eol_style_native ; 
 scalar_t__ svn_subst_eol_style_none ; 
 int /*<<< orphan*/ * svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_translation_required (scalar_t__,char const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_wc__get_translate_info (scalar_t__*,char const**,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_translated_stream(svn_stream_t **stream,
                                   svn_wc__db_t *db,
                                   const char *local_abspath,
                                   const char *versioned_abspath,
                                   apr_uint32_t flags,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  svn_boolean_t special;
  svn_boolean_t to_nf = flags & SVN_WC_TRANSLATE_TO_NF;
  svn_subst_eol_style_t style;
  const char *eol;
  apr_hash_t *keywords;
  svn_boolean_t repair_forced = flags & SVN_WC_TRANSLATE_FORCE_EOL_REPAIR;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(versioned_abspath));

  SVN_ERR(svn_wc__get_translate_info(&style, &eol,
                                     &keywords,
                                     &special,
                                     db, versioned_abspath, NULL, FALSE,
                                     scratch_pool, scratch_pool));

  if (special)
    {
      if (to_nf)
        return svn_subst_read_specialfile(stream, local_abspath, result_pool,
                                          scratch_pool);

      return svn_subst_create_specialfile(stream, local_abspath, result_pool,
                                          scratch_pool);
    }

  if (to_nf)
    SVN_ERR(svn_stream_open_readonly(stream, local_abspath, result_pool,
                                     scratch_pool));
  else
    {
      apr_file_t *file;

      /* We don't want the "open-exclusively" feature of the normal
         svn_stream_open_writable interface. Do this manually. */
      SVN_ERR(svn_io_file_open(&file, local_abspath,
                               APR_CREATE | APR_WRITE | APR_BUFFERED,
                               APR_OS_DEFAULT, result_pool));
      *stream = svn_stream_from_aprfile2(file, FALSE, result_pool);
    }

  if (svn_subst_translation_required(style, eol, keywords, special, TRUE))
    {
      if (to_nf)
        {
          if (style == svn_subst_eol_style_native)
            eol = SVN_SUBST_NATIVE_EOL_STR;
          else if (style == svn_subst_eol_style_fixed)
            repair_forced = TRUE;
          else if (style != svn_subst_eol_style_none)
            return svn_error_create(SVN_ERR_IO_UNKNOWN_EOL, NULL, NULL);

          /* Wrap the stream to translate to normal form */
          *stream = svn_subst_stream_translated(*stream,
                                                eol,
                                                repair_forced,
                                                keywords,
                                                FALSE /* expand */,
                                                result_pool);

          /* streams enforce our contract that TO_NF streams are read-only
           * by returning SVN_ERR_STREAM_NOT_SUPPORTED when trying to
           * write to them. */
        }
      else
        {
          *stream = svn_subst_stream_translated(*stream, eol, TRUE,
                                                keywords, TRUE, result_pool);

          /* streams enforce our contract that FROM_NF streams are write-only
           * by returning SVN_ERR_STREAM_NOT_SUPPORTED when trying to
           * read them. */
        }
    }

  return SVN_NO_ERROR;
}