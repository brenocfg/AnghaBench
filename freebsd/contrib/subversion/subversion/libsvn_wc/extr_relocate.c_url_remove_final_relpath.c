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
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

__attribute__((used)) static const char *
url_remove_final_relpath(const char *url,
                         const char *relpath,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  char *result = apr_pstrdup(result_pool, url);
  char *result_end;
  const char *relpath_end;

  SVN_ERR_ASSERT_NO_RETURN(svn_path_is_url(url));
  SVN_ERR_ASSERT_NO_RETURN(svn_relpath_is_canonical(relpath));

  if (relpath[0] == 0)
    return result;

  relpath = svn_path_uri_encode(relpath, scratch_pool);
  result_end = result + strlen(result) - 1;
  relpath_end = relpath + strlen(relpath) - 1;

  while (relpath_end >= relpath)
    {
      if (*result_end != *relpath_end)
        return NULL;

      relpath_end--;
      result_end--;
    }

  if (*result_end != '/')
    return NULL;

  *result_end = 0;

  return result;
}