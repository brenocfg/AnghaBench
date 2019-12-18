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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_temp_dir_get (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_dir ; 

__attribute__((used)) static svn_error_t *
init_temp_dir(void *baton, apr_pool_t *scratch_pool)
{
  /* Global pool for the temp path */
  apr_pool_t *global_pool = svn_pool_create(NULL);
  const char *dir;

  apr_status_t apr_err = apr_temp_dir_get(&dir, scratch_pool);

  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't find a temporary directory"));

  SVN_ERR(cstring_to_utf8(&dir, dir, scratch_pool));

  dir = svn_dirent_internal_style(dir, scratch_pool);

  SVN_ERR(svn_dirent_get_absolute(&temp_dir, dir, global_pool));

  return SVN_NO_ERROR;
}