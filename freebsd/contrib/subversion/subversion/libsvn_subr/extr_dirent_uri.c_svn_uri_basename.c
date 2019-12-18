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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 char const* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_uri_is_root (char const*,int) ; 

const char *
svn_uri_basename(const char *uri, apr_pool_t *pool)
{
  apr_size_t len = strlen(uri);
  apr_size_t start;

  assert(svn_uri_is_canonical(uri, NULL));

  if (svn_uri_is_root(uri, len))
    return "";

  start = len;
  while (start > 0 && uri[start - 1] != '/')
    --start;

  return svn_path_uri_decode(uri + start, pool);
}