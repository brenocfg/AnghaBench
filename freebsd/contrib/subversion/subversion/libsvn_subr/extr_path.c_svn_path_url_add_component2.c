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
 char const* svn_path_join_internal (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__char_validity ; 
 char* uri_escape (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_path_url_add_component2(const char *url,
                            const char *component,
                            apr_pool_t *pool)
{
  /* = svn_path_uri_encode() but without always copying */
  component = uri_escape(component, svn_uri__char_validity, pool);

  return svn_path_join_internal(url, component, pool);
}