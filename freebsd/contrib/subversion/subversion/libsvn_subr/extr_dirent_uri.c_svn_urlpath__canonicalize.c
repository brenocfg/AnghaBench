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
 char* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_urlpath__canonicalize(const char *uri,
                          apr_pool_t *pool)
{
  if (svn_path_is_url(uri))
    {
      uri = svn_uri_canonicalize(uri, pool);
    }
  else
    {
      uri = svn_fspath__canonicalize(uri, pool);
      /* Do a little dance to normalize hex encoding. */
      uri = svn_path_uri_decode(uri, pool);
      uri = svn_path_uri_encode(uri, pool);
    }
  return uri;
}