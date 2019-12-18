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
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static svn_error_t *get_fs_path(const char *repos_url, const char *url,
                                const char **fs_path)
{
  apr_size_t len;

  len = strlen(repos_url);
  if (strncmp(url, repos_url, len) != 0)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             "'%s' is not the same repository as '%s'",
                             url, repos_url);
  *fs_path = url + len;
  if (! **fs_path)
    *fs_path = "/";

  return SVN_NO_ERROR;
}