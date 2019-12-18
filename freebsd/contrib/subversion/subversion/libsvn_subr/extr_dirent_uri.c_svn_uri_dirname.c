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
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_uri_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uri_previous_segment (char const*,int /*<<< orphan*/ ) ; 

char *
svn_uri_dirname(const char *uri, apr_pool_t *pool)
{
  apr_size_t len = strlen(uri);

  assert(svn_uri_is_canonical(uri, pool));

  if (svn_uri_is_root(uri, len))
    return apr_pstrmemdup(pool, uri, len);
  else
    return apr_pstrmemdup(pool, uri, uri_previous_segment(uri, len));
}