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
 int /*<<< orphan*/  assert (int) ; 
 char* svn_fspath__basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__dirname (char const*,int /*<<< orphan*/ *) ; 

void
svn_fspath__split(const char **dirpath,
                  const char **base_name,
                  const char *fspath,
                  apr_pool_t *result_pool)
{
  assert(dirpath != base_name);

  if (dirpath)
    *dirpath = svn_fspath__dirname(fspath, result_pool);

  if (base_name)
    *base_name = svn_fspath__basename(fspath, result_pool);
}