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
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_illegal_path_escape (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_newline(const char *path, apr_pool_t *pool)
{
  char *c = strchr(path, '\n');

  if (c)
    return svn_error_createf(SVN_ERR_FS_PATH_SYNTAX, NULL,
       _("Invalid control character '0x%02x' in path '%s'"),
       (unsigned char)*c, svn_path_illegal_path_escape(path, pool));

  return SVN_NO_ERROR;
}