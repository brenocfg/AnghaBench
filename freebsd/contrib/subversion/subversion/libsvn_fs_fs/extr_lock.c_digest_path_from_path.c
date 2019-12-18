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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGEST_SUBDIR_LEN ; 
 int /*<<< orphan*/  PATH_LOCKS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_digest (char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join_many (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
digest_path_from_path(const char **digest_path,
                      const char *fs_path,
                      const char *path,
                      apr_pool_t *pool)
{
  const char *digest;
  SVN_ERR(make_digest(&digest, path, pool));
  *digest_path = svn_dirent_join_many(pool, fs_path, PATH_LOCKS_DIR,
                                      apr_pstrmemdup(pool, digest,
                                                     DIGEST_SUBDIR_LEN),
                                      digest, SVN_VA_NULL);
  return SVN_NO_ERROR;
}