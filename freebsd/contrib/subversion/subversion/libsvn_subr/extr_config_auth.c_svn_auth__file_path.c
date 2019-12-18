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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG__AUTH_SUBDIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_user_config_path (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_auth__file_path(const char **path,
                    const char *cred_kind,
                    const char *realmstring,
                    const char *config_dir,
                    apr_pool_t *pool)
{
  const char *authdir_path, *hexname;
  svn_checksum_t *checksum;

  /* Construct the path to the directory containing the creds files,
     e.g. "~/.subversion/auth/svn.simple".  The last component is
     simply the cred_kind.  */
  SVN_ERR(svn_config_get_user_config_path(&authdir_path, config_dir,
                                          SVN_CONFIG__AUTH_SUBDIR, pool));
  if (authdir_path)
    {
      authdir_path = svn_dirent_join(authdir_path, cred_kind, pool);

      /* Construct the basename of the creds file.  It's just the
         realmstring converted into an md5 hex string.  */
      SVN_ERR(svn_checksum(&checksum, svn_checksum_md5, realmstring,
                           strlen(realmstring), pool));
      hexname = svn_checksum_to_cstring(checksum, pool);

      *path = svn_dirent_join(authdir_path, hexname, pool);
    }
  else
    *path = NULL;

  return SVN_NO_ERROR;
}