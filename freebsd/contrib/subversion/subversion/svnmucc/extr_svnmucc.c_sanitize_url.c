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
 char* svn_path_uri_autoescape (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_from_iri (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
sanitize_url(const char *url,
             apr_pool_t *pool)
{
  url = svn_path_uri_from_iri(url, pool);
  url = svn_path_uri_autoescape(url, pool);
  return svn_uri_canonicalize(url, pool);
}