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
 char* svn_path_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 

const char *
svn_path_url_add_component(const char *url,
                           const char *component,
                           apr_pool_t *pool)
{
  /* URL can have trailing '/' */
  url = svn_path_canonicalize(url, pool);

  return svn_path_url_add_component2(url, component, pool);
}