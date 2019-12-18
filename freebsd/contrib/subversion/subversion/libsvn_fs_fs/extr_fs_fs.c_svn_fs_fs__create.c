#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int minor; } ;
typedef  TYPE_1__ svn_version_t ;
struct TYPE_8__ {scalar_t__ config; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_INT32_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_LOG_ADDRESSING ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_SHARD_SIZE ; 
 int SVN_FS_FS_DEFAULT_MAX_FILES_PER_DIR ; 
 int SVN_FS_FS__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cstring_strtoi64 (scalar_t__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__compatible_version (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__create_file_tree (TYPE_2__*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_format (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash__get_bool (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_fs__create(svn_fs_t *fs,
                  const char *path,
                  apr_pool_t *pool)
{
  int format = SVN_FS_FS__FORMAT_NUMBER;
  int shard_size = SVN_FS_FS_DEFAULT_MAX_FILES_PER_DIR;
  svn_boolean_t log_addressing;

  /* Process the given filesystem config. */
  if (fs->config)
    {
      svn_version_t *compatible_version;
      const char *shard_size_str;
      SVN_ERR(svn_fs__compatible_version(&compatible_version, fs->config,
                                         pool));

      /* select format number */
      switch(compatible_version->minor)
        {
          case 0: return svn_error_create(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
                 _("FSFS is not compatible with Subversion prior to 1.1"));

          case 1:
          case 2:
          case 3: format = 1;
                  break;

          case 4: format = 2;
                  break;

          case 5: format = 3;
                  break;

          case 6:
          case 7: format = 4;
                  break;

          case 8: format = 6;
                  break;
          case 9: format = 7;
                  break;

          default:format = SVN_FS_FS__FORMAT_NUMBER;
        }

      shard_size_str = svn_hash_gets(fs->config, SVN_FS_CONFIG_FSFS_SHARD_SIZE);
      if (shard_size_str)
        {
          apr_int64_t val;
          SVN_ERR(svn_cstring_strtoi64(&val, shard_size_str, 0,
                                       APR_INT32_MAX, 10));

          shard_size = (int) val;
        }
    }

  log_addressing = svn_hash__get_bool(fs->config,
                                      SVN_FS_CONFIG_FSFS_LOG_ADDRESSING,
                                      TRUE);

  /* Actual FS creation. */
  SVN_ERR(svn_fs_fs__create_file_tree(fs, path, format, shard_size,
                                      log_addressing, pool));

  /* This filesystem is ready.  Stamp it with a format number. */
  SVN_ERR(svn_fs_fs__write_format(fs, FALSE, pool));

  return SVN_NO_ERROR;
}