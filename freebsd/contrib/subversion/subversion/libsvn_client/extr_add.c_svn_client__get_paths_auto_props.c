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
typedef  int /*<<< orphan*/  svn_magic__cookie_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  mimetypes_map; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_auto_props_for_pattern (int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_detect_mimetype2 (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_is_file_executable (scalar_t__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_magic__detect_binary_mimetype (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create_empty (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_paths_auto_props(apr_hash_t **properties,
                                 const char **mimetype,
                                 const char *path,
                                 svn_magic__cookie_t *magic_cookie,
                                 apr_hash_t *autoprops,
                                 svn_client_ctx_t *ctx,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_boolean_t have_executable = FALSE;

  *properties = apr_hash_make(result_pool);
  *mimetype = NULL;

  if (autoprops)
    {
      for (hi = apr_hash_first(scratch_pool, autoprops);
           hi != NULL;
           hi = apr_hash_next(hi))
        {
          const char *pattern = apr_hash_this_key(hi);
          apr_hash_t *propvals = apr_hash_this_val(hi);

          get_auto_props_for_pattern(*properties, mimetype, &have_executable,
                                     svn_dirent_basename(path, scratch_pool),
                                     pattern, propvals, scratch_pool);
        }
    }

  /* if mimetype has not been set check the file */
  if (! *mimetype)
    {
      SVN_ERR(svn_io_detect_mimetype2(mimetype, path, ctx->mimetypes_map,
                                      result_pool));

      /* If we got no mime-type, or if it is "application/octet-stream",
       * try to get the mime-type from libmagic. */
      if (magic_cookie &&
          (!*mimetype ||
           strcmp(*mimetype, "application/octet-stream") == 0))
        {
          const char *magic_mimetype;

         /* Since libmagic usually treats UTF-16 files as "text/plain",
          * svn_magic__detect_binary_mimetype() will return NULL for such
          * files. This is fine for now since we currently don't support
          * UTF-16-encoded text files (issue #2194).
          * Once we do support UTF-16 this code path will fail to detect
          * them as text unless the svn_io_detect_mimetype2() call above
          * returns "text/plain" for them. */
          SVN_ERR(svn_magic__detect_binary_mimetype(&magic_mimetype,
                                                    path, magic_cookie,
                                                    result_pool,
                                                    scratch_pool));
          if (magic_mimetype)
            *mimetype = magic_mimetype;
        }

      if (*mimetype)
        apr_hash_set(*properties, SVN_PROP_MIME_TYPE,
                     strlen(SVN_PROP_MIME_TYPE),
                     svn_string_create(*mimetype, result_pool));
    }

  /* if executable has not been set check the file */
  if (! have_executable)
    {
      svn_boolean_t executable = FALSE;
      SVN_ERR(svn_io_is_file_executable(&executable, path, scratch_pool));
      if (executable)
        apr_hash_set(*properties, SVN_PROP_EXECUTABLE,
                     strlen(SVN_PROP_EXECUTABLE),
                     svn_string_create_empty(result_pool));
    }

  return SVN_NO_ERROR;
}