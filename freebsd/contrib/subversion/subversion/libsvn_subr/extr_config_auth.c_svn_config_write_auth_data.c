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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_REALMSTRING_KEY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_NO_AUTH_FILE_PATH ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_auth__file_path (char const**,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_write_auth_data(apr_hash_t *hash,
                           const char *cred_kind,
                           const char *realmstring,
                           const char *config_dir,
                           apr_pool_t *pool)
{
  svn_stream_t *stream;
  const char *auth_path, *tmp_path;

  SVN_ERR(svn_auth__file_path(&auth_path, cred_kind, realmstring, config_dir,
                              pool));
  if (! auth_path)
    return svn_error_create(SVN_ERR_NO_AUTH_FILE_PATH, NULL,
                            _("Unable to locate auth file"));

  /* Add the realmstring to the hash, so programs (or users) can
     verify exactly which set of credentials this file holds.
     ### What if realmstring key is already in the hash? */
  svn_hash_sets(hash, SVN_CONFIG_REALMSTRING_KEY,
                svn_string_create(realmstring, pool));

  SVN_ERR_W(svn_stream_open_unique(&stream, &tmp_path,
                                   svn_dirent_dirname(auth_path, pool),
                                   svn_io_file_del_on_pool_cleanup,
                                   pool, pool),
            _("Unable to open auth file for writing"));
  SVN_ERR_W(svn_hash_write2(hash, stream, SVN_HASH_TERMINATOR, pool),
            apr_psprintf(pool, _("Error writing hash to '%s'"),
                         svn_dirent_local_style(auth_path, pool)));
  SVN_ERR(svn_stream_close(stream));
  SVN_ERR(svn_io_file_rename2(tmp_path, auth_path, FALSE, pool));

  /* To be nice, remove the realmstring from the hash again, just in
     case the caller wants their hash unchanged.
     ### Should we also do this when a write error occurs? */
  svn_hash_sets(hash, SVN_CONFIG_REALMSTRING_KEY, NULL);

  return SVN_NO_ERROR;
}