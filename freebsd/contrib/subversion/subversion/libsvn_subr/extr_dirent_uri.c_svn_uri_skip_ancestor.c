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
 char const* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 char* uri_skip_ancestor (char const*,char const*) ; 

const char *
svn_uri_skip_ancestor(const char *parent_uri,
                      const char *child_uri,
                      apr_pool_t *result_pool)
{
  const char *result = uri_skip_ancestor(parent_uri, child_uri);

  return result ? svn_path_uri_decode(result, result_pool) : NULL;
}