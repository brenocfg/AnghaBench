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
typedef  scalar_t__ svn_io_file_del_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct temp_file_cleanup_s {int /*<<< orphan*/ * fname_apr; int /*<<< orphan*/ * pool; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int32_t ;
struct TYPE_3__ {scalar_t__ filetype; } ;
typedef  TYPE_1__ apr_finfo_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BINARY ; 
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int APR_DELONCLOSE ; 
 scalar_t__ APR_DIR ; 
 int APR_EXCL ; 
 int /*<<< orphan*/  APR_FINFO_TYPE ; 
 scalar_t__ APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 scalar_t__ APR_STATUS_IS_EACCES (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EEXIST (scalar_t__) ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNIQUE_NAMES_EXHAUSTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 struct temp_file_cleanup_s* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,struct temp_file_cleanup_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_stat (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_io_file_del_on_close ; 
 scalar_t__ svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_temp_dir (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_file_child_cleanup_handler ; 
 int /*<<< orphan*/  temp_file_plain_cleanup_handler ; 

svn_error_t *
svn_io_open_uniquely_named(apr_file_t **file,
                           const char **unique_path,
                           const char *dirpath,
                           const char *filename,
                           const char *suffix,
                           svn_io_file_del_t delete_when,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const char *path;
  unsigned int i;
  struct temp_file_cleanup_s *baton = NULL;

  /* At the beginning, we don't know whether unique_path will need
     UTF8 conversion */
  svn_boolean_t needs_utf8_conversion = TRUE;

  SVN_ERR_ASSERT(file || unique_path);

  if (dirpath == NULL)
    SVN_ERR(svn_io_temp_dir(&dirpath, scratch_pool));
  if (filename == NULL)
    filename = "tempfile";
  if (suffix == NULL)
    suffix = ".tmp";

  path = svn_dirent_join(dirpath, filename, scratch_pool);

  if (delete_when == svn_io_file_del_on_pool_cleanup)
    {
      baton = apr_palloc(result_pool, sizeof(*baton));

      baton->pool = result_pool;
      baton->fname_apr = NULL;

      /* Because cleanups are run LIFO, we need to make sure to register
         our cleanup before the apr_file_close cleanup:

         On Windows, you can't remove an open file.
      */
      apr_pool_cleanup_register(result_pool, baton,
                                temp_file_plain_cleanup_handler,
                                temp_file_child_cleanup_handler);
    }

  for (i = 1; i <= 99999; i++)
    {
      const char *unique_name;
      const char *unique_name_apr;
      apr_file_t *try_file;
      apr_status_t apr_err;
      apr_int32_t flag = (APR_READ | APR_WRITE | APR_CREATE | APR_EXCL
                          | APR_BUFFERED | APR_BINARY);

      if (delete_when == svn_io_file_del_on_close)
        flag |= APR_DELONCLOSE;

      /* Special case the first attempt -- if we can avoid having a
         generated numeric portion at all, that's best.  So first we
         try with just the suffix; then future tries add a number
         before the suffix.  (A do-while loop could avoid the repeated
         conditional, but it's not worth the clarity loss.)

         If the first attempt fails, the first number will be "2".
         This is good, since "1" would misleadingly imply that
         the second attempt was actually the first... and if someone's
         got conflicts on their conflicts, we probably don't want to
         add to their confusion :-). */
      if (i == 1)
        unique_name = apr_psprintf(scratch_pool, "%s%s", path, suffix);
      else
        unique_name = apr_psprintf(scratch_pool, "%s.%u%s", path, i, suffix);

      /* Hmmm.  Ideally, we would append to a native-encoding buf
         before starting iteration, then convert back to UTF-8 for
         return. But I suppose that would make the appending code
         sensitive to i18n in a way it shouldn't be... Oh well. */
      if (needs_utf8_conversion)
        {
          SVN_ERR(cstring_from_utf8(&unique_name_apr, unique_name,
                                    scratch_pool));
          if (i == 1)
            {
              /* The variable parts of unique_name will not require UTF8
                 conversion. Therefore, if UTF8 conversion had no effect
                 on it in the first iteration, it won't require conversion
                 in any future iteration. */
              needs_utf8_conversion = strcmp(unique_name_apr, unique_name);
            }
        }
      else
        unique_name_apr = unique_name;

      apr_err = file_open(&try_file, unique_name_apr, flag,
                          APR_OS_DEFAULT, FALSE, result_pool);

      if (APR_STATUS_IS_EEXIST(apr_err))
        continue;
      else if (apr_err)
        {
          /* On Win32, CreateFile fails with an "Access Denied" error
             code, rather than "File Already Exists", if the colliding
             name belongs to a directory. */
          if (APR_STATUS_IS_EACCES(apr_err))
            {
              apr_finfo_t finfo;
              apr_status_t apr_err_2 = apr_stat(&finfo, unique_name_apr,
                                                APR_FINFO_TYPE, scratch_pool);

              if (!apr_err_2 && finfo.filetype == APR_DIR)
                continue;

#ifdef WIN32
              if (apr_err == APR_FROM_OS_ERROR(ERROR_ACCESS_DENIED) ||
                  apr_err == APR_FROM_OS_ERROR(ERROR_SHARING_VIOLATION))
                {
                  /* The file is in use by another process or is hidden;
                     create a new name, but don't do this 99999 times in
                     case the folder is not writable */
                  i += 797;
                  continue;
                }
#endif

              /* Else fall through and return the original error. */
            }

          if (file)
            *file = NULL;
          if (unique_path)
            *unique_path = NULL;
          return svn_error_wrap_apr(apr_err, _("Can't open '%s'"),
                                    svn_dirent_local_style(unique_name,
                                                         scratch_pool));
        }
      else
        {
          if (delete_when == svn_io_file_del_on_pool_cleanup)
            baton->fname_apr = apr_pstrdup(result_pool, unique_name_apr);

          if (file)
            *file = try_file;
          else
            apr_file_close(try_file);
          if (unique_path)
            *unique_path = apr_pstrdup(result_pool, unique_name);

          return SVN_NO_ERROR;
        }
    }

  if (file)
    *file = NULL;
  if (unique_path)
    *unique_path = NULL;
  return svn_error_createf(SVN_ERR_IO_UNIQUE_NAMES_EXHAUSTED,
                           NULL,
                           _("Unable to make name for '%s'"),
                           svn_dirent_local_style(path, scratch_pool));
}