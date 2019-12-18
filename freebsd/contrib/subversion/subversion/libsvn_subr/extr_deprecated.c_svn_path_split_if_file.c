#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {scalar_t__ filetype; } ;
typedef  TYPE_2__ apr_finfo_t ;

/* Variables and functions */
 scalar_t__ APR_DIR ; 
 int /*<<< orphan*/  APR_FINFO_TYPE ; 
 scalar_t__ APR_REG ; 
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 char* SVN_EMPTY_PATH ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_FILENAME ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_io_stat (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_split (char const*,char const**,char const**,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_path_split_if_file(const char *path,
                       const char **pdirectory,
                       const char **pfile,
                       apr_pool_t *pool)
{
  apr_finfo_t finfo;
  svn_error_t *err;

  SVN_ERR_ASSERT(svn_path_is_canonical(path, pool));

  err = svn_io_stat(&finfo, path, APR_FINFO_TYPE, pool);
  if (err && ! APR_STATUS_IS_ENOENT(err->apr_err))
    return err;

  if (err || finfo.filetype == APR_REG)
    {
      svn_error_clear(err);
      svn_path_split(path, pdirectory, pfile, pool);
    }
  else if (finfo.filetype == APR_DIR)
    {
      *pdirectory = path;
      *pfile = SVN_EMPTY_PATH;
    }
  else
    {
      return svn_error_createf(SVN_ERR_BAD_FILENAME, NULL,
                               _("'%s' is neither a file nor a directory name"),
                               svn_path_local_style(path, pool));
    }

  return SVN_NO_ERROR;
}