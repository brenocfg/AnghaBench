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
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 

const char *
svn_cl__local_style_skip_ancestor(const char *parent_path,
                                  const char *path,
                                  apr_pool_t *pool)
{
  const char *relpath = NULL;

  if (parent_path)
    relpath = svn_dirent_skip_ancestor(parent_path, path);

  return svn_dirent_local_style(relpath ? relpath : path, pool);
}