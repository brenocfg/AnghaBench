#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int minor; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int /*<<< orphan*/  svn_mutex__t ;
struct TYPE_11__ {scalar_t__ fsap_data; int /*<<< orphan*/  path; scalar_t__ config; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {int format; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_FILE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_BASE__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cleanup_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * open_databases (TYPE_2__*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  populate_opened_fs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__compatible_version (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_init_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_io_write_version_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
base_create(svn_fs_t *fs,
            const char *path,
            svn_mutex__t *common_pool_lock,
            apr_pool_t *scratch_pool,
            apr_pool_t *common_pool)
{
  int format = SVN_FS_BASE__FORMAT_NUMBER;
  svn_error_t *svn_err;

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
          case 3: format = 1;
                  break;

          case 4: format = 2;
                  break;

          case 5: format = 3;
                  break;

          default:format = SVN_FS_BASE__FORMAT_NUMBER;
        }
    }

  /* Create the environment and databases. */
  svn_err = open_databases(fs, TRUE, format, path);
  if (svn_err) goto error;

  /* Initialize the DAG subsystem. */
  svn_err = svn_fs_base__dag_init_fs(fs);
  if (svn_err) goto error;

  /* This filesystem is ready.  Stamp it with a format number. */
  svn_err = svn_io_write_version_file(svn_dirent_join(fs->path, FORMAT_FILE,
                                                      scratch_pool),
                                      format, scratch_pool);
  if (svn_err) goto error;

  ((base_fs_data_t *) fs->fsap_data)->format = format;

  SVN_ERR(populate_opened_fs(fs, scratch_pool));
  return SVN_NO_ERROR;

error:
  return svn_error_compose_create(svn_err,
                                  svn_error_trace(cleanup_fs(fs)));
}