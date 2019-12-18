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
 int /*<<< orphan*/  internal_style (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_relpath__internal_style(const char *relpath,
                            apr_pool_t *pool)
{
  return svn_relpath_canonicalize(internal_style(relpath, pool), pool);
}