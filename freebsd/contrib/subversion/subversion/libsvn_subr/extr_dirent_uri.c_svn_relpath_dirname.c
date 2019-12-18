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
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relpath_is_canonical (char const*) ; 
 int /*<<< orphan*/  relpath_previous_segment (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
svn_relpath_dirname(const char *relpath,
                    apr_pool_t *pool)
{
  apr_size_t len = strlen(relpath);

  assert(relpath_is_canonical(relpath));

  return apr_pstrmemdup(pool, relpath,
                        relpath_previous_segment(relpath, len));
}