#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_38__ {char const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_39__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_40__ {scalar_t__ mtime; scalar_t__ size; } ;
typedef  TYPE_3__ apr_finfo_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOL_STR ; 
 int /*<<< orphan*/  APR_FILEPATH_NATIVE ; 
 int APR_FINFO_MTIME ; 
 int APR_FINFO_SIZE ; 
 scalar_t__ APR_STATUS_IS_EACCES (scalar_t__) ; 
 scalar_t__ EROFS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_EXTERNAL_PROGRAM ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_filepath_get (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_filepath_set (char const*,int /*<<< orphan*/ *) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 scalar_t__ apr_time_from_sec (int) ; 
 TYPE_2__* find_editor_binary (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__* svn_error_quick_wrap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_handle_error2 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 TYPE_2__* svn_io_file_write_full (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_open_uniquely_named (int /*<<< orphan*/ **,char const**,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_set_file_affected_time (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_stat (TYPE_3__*,char const*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_temp_dir (char const**,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_string_create_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_string_dup (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stringbuf_from_file2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_subst_translate_cstring2 (char const*,char const**,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_subst_translate_string2 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_utf_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_utf_cstring_from_utf8_ex2 (char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 int system (char const*) ; 

svn_error_t *
svn_cmdline__edit_string_externally(svn_string_t **edited_contents /* UTF-8! */,
                                    const char **tmpfile_left /* UTF-8! */,
                                    const char *editor_cmd,
                                    const char *base_dir /* UTF-8! */,
                                    const svn_string_t *contents /* UTF-8! */,
                                    const char *filename,
                                    apr_hash_t *config,
                                    svn_boolean_t as_text,
                                    const char *encoding,
                                    apr_pool_t *pool)
{
  const char *editor;
  const char *cmd;
  apr_file_t *tmp_file;
  const char *tmpfile_name;
  const char *tmpfile_native;
  const char *base_dir_apr;
  svn_string_t *translated_contents;
  apr_status_t apr_err;
  apr_size_t written;
  apr_finfo_t finfo_before, finfo_after;
  svn_error_t *err = SVN_NO_ERROR;
  char *old_cwd;
  int sys_err;
  svn_boolean_t remove_file = TRUE;

  SVN_ERR(find_editor_binary(&editor, editor_cmd, config));

  /* Convert file contents from UTF-8/LF if desired. */
  if (as_text)
    {
      const char *translated;
      SVN_ERR(svn_subst_translate_cstring2(contents->data, &translated,
                                           APR_EOL_STR, FALSE,
                                           NULL, FALSE, pool));
      translated_contents = svn_string_create_empty(pool);
      if (encoding)
        SVN_ERR(svn_utf_cstring_from_utf8_ex2(&translated_contents->data,
                                              translated, encoding, pool));
      else
        SVN_ERR(svn_utf_cstring_from_utf8(&translated_contents->data,
                                          translated, pool));
      translated_contents->len = strlen(translated_contents->data);
    }
  else
    translated_contents = svn_string_dup(contents, pool);

  /* Move to BASE_DIR to avoid getting characters that need quoting
     into tmpfile_name */
  apr_err = apr_filepath_get(&old_cwd, APR_FILEPATH_NATIVE, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't get working directory"));

  /* APR doesn't like "" directories */
  if (base_dir[0] == '\0')
    base_dir_apr = ".";
  else
    SVN_ERR(svn_path_cstring_from_utf8(&base_dir_apr, base_dir, pool));
  apr_err = apr_filepath_set(base_dir_apr, pool);
  if (apr_err)
    {
      return svn_error_wrap_apr
        (apr_err, _("Can't change working directory to '%s'"), base_dir);
    }

  /*** From here on, any problems that occur require us to cd back!! ***/

  /* Ask the working copy for a temporary file named FILENAME-something. */
  err = svn_io_open_uniquely_named(&tmp_file, &tmpfile_name,
                                   "" /* dirpath */,
                                   filename,
                                   ".tmp",
                                   svn_io_file_del_none, pool, pool);

  if (err && (APR_STATUS_IS_EACCES(err->apr_err) || err->apr_err == EROFS))
    {
      const char *temp_dir_apr;

      svn_error_clear(err);

      SVN_ERR(svn_io_temp_dir(&base_dir, pool));

      SVN_ERR(svn_path_cstring_from_utf8(&temp_dir_apr, base_dir, pool));
      apr_err = apr_filepath_set(temp_dir_apr, pool);
      if (apr_err)
        {
          return svn_error_wrap_apr
            (apr_err, _("Can't change working directory to '%s'"), base_dir);
        }

      err = svn_io_open_uniquely_named(&tmp_file, &tmpfile_name,
                                       "" /* dirpath */,
                                       filename,
                                       ".tmp",
                                       svn_io_file_del_none, pool, pool);
    }

  if (err)
    goto cleanup2;

  /*** From here on, any problems that occur require us to cleanup
       the file we just created!! ***/

  /* Dump initial CONTENTS to TMP_FILE. */
  err = svn_io_file_write_full(tmp_file, translated_contents->data,
                               translated_contents->len, &written,
                               pool);

  err = svn_error_compose_create(err, svn_io_file_close(tmp_file, pool));

  /* Make sure the whole CONTENTS were written, else return an error. */
  if (err)
    goto cleanup;

  /* Get information about the temporary file before the user has
     been allowed to edit its contents. */
  err = svn_io_stat(&finfo_before, tmpfile_name, APR_FINFO_MTIME, pool);
  if (err)
    goto cleanup;

  /* Backdate the file a little bit in case the editor is very fast
     and doesn't change the size.  (Use two seconds, since some
     filesystems have coarse granularity.)  It's OK if this call
     fails, so we don't check its return value.*/
  err = svn_io_set_file_affected_time(finfo_before.mtime
                                              - apr_time_from_sec(2),
                                      tmpfile_name, pool);
  svn_error_clear(err);

  /* Stat it again to get the mtime we actually set. */
  err = svn_io_stat(&finfo_before, tmpfile_name,
                    APR_FINFO_MTIME | APR_FINFO_SIZE, pool);
  if (err)
    goto cleanup;

  /* Prepare the editor command line.  */
  err = svn_utf_cstring_from_utf8(&tmpfile_native, tmpfile_name, pool);
  if (err)
    goto cleanup;
  cmd = apr_psprintf(pool, "%s %s", editor, tmpfile_native);

  /* If the caller wants us to leave the file around, return the path
     of the file we'll use, and make a note not to destroy it.  */
  if (tmpfile_left)
    {
      *tmpfile_left = svn_dirent_join(base_dir, tmpfile_name, pool);
      remove_file = FALSE;
    }

  /* Now, run the editor command line.  */
  sys_err = system(cmd);
  if (sys_err != 0)
    {
      /* Extracting any meaning from sys_err is platform specific, so just
         use the raw value. */
      err =  svn_error_createf(SVN_ERR_EXTERNAL_PROGRAM, NULL,
                               _("system('%s') returned %d"), cmd, sys_err);
      goto cleanup;
    }

  /* Get information about the temporary file after the assumed editing. */
  err = svn_io_stat(&finfo_after, tmpfile_name,
                    APR_FINFO_MTIME | APR_FINFO_SIZE, pool);
  if (err)
    goto cleanup;

  /* If the file looks changed... */
  if ((finfo_before.mtime != finfo_after.mtime) ||
      (finfo_before.size != finfo_after.size))
    {
      svn_stringbuf_t *edited_contents_s;
      err = svn_stringbuf_from_file2(&edited_contents_s, tmpfile_name, pool);
      if (err)
        goto cleanup;

      *edited_contents = svn_stringbuf__morph_into_string(edited_contents_s);

      /* Translate back to UTF8/LF if desired. */
      if (as_text)
        {
          err = svn_subst_translate_string2(edited_contents, NULL, NULL,
                                            *edited_contents, encoding, FALSE,
                                            pool, pool);
          if (err)
            {
              err = svn_error_quick_wrap
                (err,
                 _("Error normalizing edited contents to internal format"));
              goto cleanup;
            }
        }
    }
  else
    {
      /* No edits seem to have been made */
      *edited_contents = NULL;
    }

 cleanup:
  if (remove_file)
    {
      /* Remove the file from disk.  */
      err = svn_error_compose_create(
              err,
              svn_io_remove_file2(tmpfile_name, FALSE, pool));
    }

 cleanup2:
  /* If we against all probability can't cd back, all further relative
     file references would be screwed up, so we have to abort. */
  apr_err = apr_filepath_set(old_cwd, pool);
  if (apr_err)
    {
      svn_handle_error2(svn_error_wrap_apr
                        (apr_err, _("Can't restore working directory")),
                        stderr, TRUE /* fatal */, "svn: ");
    }

  return svn_error_trace(err);
}