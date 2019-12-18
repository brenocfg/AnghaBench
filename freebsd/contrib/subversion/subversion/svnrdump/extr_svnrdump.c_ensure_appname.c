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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
ensure_appname(const char *progname,
               apr_pool_t *pool)
{
  if (!progname)
    return "svnrdump";

  return svn_dirent_basename(svn_dirent_internal_style(progname, pool), NULL);
}