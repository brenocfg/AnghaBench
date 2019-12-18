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
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  config_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * get_file_config (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_generic_config (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_repos_config (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 

svn_error_t *
svn_repos__get_config(svn_stream_t **stream,
                      svn_checksum_t **checksum,
                      config_access_t *access,
                      const char *path,
                      svn_boolean_t must_exist,
                      apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  /* Directly access the config data. */
  if (svn_path_is_url(path))
    err = get_repos_config(stream, checksum, access, path, must_exist,
                           scratch_pool);
  else
    err = get_file_config(stream, checksum, access, path, must_exist,
                          scratch_pool);

  /* Fallback to indirect access using the generic config file parser.
   * This is mainly used for registry support under Win32. */
  if (err)
    {
      svn_error_t *err2 = get_generic_config(stream, checksum, access, path,
                                             must_exist, scratch_pool);
      if (err2)
        {
          svn_error_clear(err2);
        }
      else
        {
          svn_error_clear(err);
          err = SVN_NO_ERROR;
        }
    }

  return svn_error_trace(err);
}