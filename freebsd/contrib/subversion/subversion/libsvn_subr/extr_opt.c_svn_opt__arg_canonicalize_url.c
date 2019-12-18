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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char SVN_PATH_LOCAL_SEPARATOR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_path_is_backpath_present (char const*) ; 
 char* svn_path_uri_autoescape (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_from_iri (char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt__arg_canonicalize_url(const char **url_out, const char *url_in,
                              apr_pool_t *pool)
{
  const char *target;

  /* Convert to URI. */
  target = svn_path_uri_from_iri(url_in, pool);
  /* Auto-escape some ASCII characters. */
  target = svn_path_uri_autoescape(target, pool);

#if '/' != SVN_PATH_LOCAL_SEPARATOR
  /* Allow using file:///C:\users\me/repos on Windows, like we did in 1.6 */
  if (strchr(target, SVN_PATH_LOCAL_SEPARATOR))
    {
      char *p = apr_pstrdup(pool, target);
      target = p;

      /* Convert all local-style separators to the canonical ones. */
      for (; *p != '\0'; ++p)
        if (*p == SVN_PATH_LOCAL_SEPARATOR)
          *p = '/';
    }
#endif

  /* Verify that no backpaths are present in the URL. */
  if (svn_path_is_backpath_present(target))
    return svn_error_createf(SVN_ERR_BAD_URL, 0,
                             _("URL '%s' contains a '..' element"),
                             target);

  /* Strip any trailing '/' and collapse other redundant elements. */
  target = svn_uri_canonicalize(target, pool);

  *url_out = target;
  return SVN_NO_ERROR;
}