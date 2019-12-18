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
 int /*<<< orphan*/  SVN_ERR_FS_PATH_SYNTAX ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_path_illegal_path_escape (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_backpath_present (char const*) ; 
 scalar_t__ svn_path_is_dotpath_present (char const*) ; 
 int /*<<< orphan*/  svn_utf__cstring_is_valid (char const*) ; 

svn_error_t *
svn_fs__path_valid(const char *path, apr_pool_t *pool)
{
  char *c;

  /* UTF-8 encoded string without NULs. */
  if (! svn_utf__cstring_is_valid(path))
    {
      return svn_error_createf(SVN_ERR_FS_PATH_SYNTAX, NULL,
                               _("Path '%s' is not in UTF-8"), path);
    }

  /* No "." or ".." elements. */
  if (svn_path_is_backpath_present(path)
      || svn_path_is_dotpath_present(path))
    {
      return svn_error_createf(SVN_ERR_FS_PATH_SYNTAX, NULL,
                               _("Path '%s' contains '.' or '..' element"),
                               path);
    }

  /* Raise an error if PATH contains a newline because svn:mergeinfo and
     friends can't handle them.  Issue #4340 describes a similar problem
     in the FSFS code itself.
   */
  c = strchr(path, '\n');
  if (c)
    {
      return svn_error_createf(SVN_ERR_FS_PATH_SYNTAX, NULL,
               _("Invalid control character '0x%02x' in path '%s'"),
               (unsigned char)*c, svn_path_illegal_path_escape(path, pool));
    }

  /* That's good enough. */
  return SVN_NO_ERROR;
}