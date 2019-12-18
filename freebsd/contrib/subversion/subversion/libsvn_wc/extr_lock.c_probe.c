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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_BAD_PATH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__internal_check_wc (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
probe(svn_wc__db_t *db,
      const char **dir,
      const char *path,
      apr_pool_t *pool)
{
  svn_node_kind_t kind;
  int wc_format = 0;

  SVN_ERR(svn_io_check_path(path, &kind, pool));
  if (kind == svn_node_dir)
    {
      const char *local_abspath;

      SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
      SVN_ERR(svn_wc__internal_check_wc(&wc_format, db, local_abspath,
                                        FALSE, pool));
    }

  /* a "version" of 0 means a non-wc directory */
  if (kind != svn_node_dir || wc_format == 0)
    {
      /* Passing a path ending in "." or ".." to svn_dirent_dirname() is
         probably always a bad idea; certainly it is in this case.
         Unfortunately, svn_dirent_dirname()'s current signature can't
         return an error, so we have to insert the protection in this
         caller, ideally the API needs a change.  See issue #1617. */
      const char *base_name = svn_dirent_basename(path, pool);
      if ((strcmp(base_name, "..") == 0)
          || (strcmp(base_name, ".") == 0))
        {
          return svn_error_createf
            (SVN_ERR_WC_BAD_PATH, NULL,
             _("Path '%s' ends in '%s', "
               "which is unsupported for this operation"),
             svn_dirent_local_style(path, pool), base_name);
        }

      *dir = svn_dirent_dirname(path, pool);
    }
  else
    *dir = path;

  return SVN_NO_ERROR;
}