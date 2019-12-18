#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int minor; } ;
typedef  TYPE_1__ svn_version_t ;
struct TYPE_9__ {scalar_t__ youngest_rev_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_10__ {scalar_t__ config; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  SVN_FS_X_DEFAULT_MAX_FILES_PER_DIR ; 
 int SVN_FS_X__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__compatible_version (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__create_file_tree (TYPE_3__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_format (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__create(svn_fs_t *fs,
                 const char *path,
                 apr_pool_t *scratch_pool)
{
  int format = SVN_FS_X__FORMAT_NUMBER;
  svn_fs_x__data_t *ffd = fs->fsap_data;

  fs->path = apr_pstrdup(fs->pool, path);
  /* See if compatibility with older versions was explicitly requested. */
  if (fs->config)
    {
      svn_version_t *compatible_version;
      SVN_ERR(svn_fs__compatible_version(&compatible_version, fs->config,
                                         scratch_pool));

      /* select format number */
      switch(compatible_version->minor)
        {
          case 0:
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8: return svn_error_create(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
                  _("FSX is not compatible with Subversion prior to 1.9"));

          default:format = SVN_FS_X__FORMAT_NUMBER;
        }
    }

  /* Actual FS creation. */
  SVN_ERR(svn_fs_x__create_file_tree(fs, path, format,
                                     SVN_FS_X_DEFAULT_MAX_FILES_PER_DIR,
                                     scratch_pool));

  /* This filesystem is ready.  Stamp it with a format number. */
  SVN_ERR(svn_fs_x__write_format(fs, FALSE, scratch_pool));

  ffd->youngest_rev_cache = 0;
  return SVN_NO_ERROR;
}