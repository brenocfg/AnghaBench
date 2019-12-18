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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 void* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int svn_dirent_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_uri_get_file_url_from_dirent(const char **url,
                                 const char *dirent,
                                 apr_pool_t *pool)
{
  assert(svn_dirent_is_canonical(dirent, pool));

  SVN_ERR(svn_dirent_get_absolute(&dirent, dirent, pool));

  dirent = svn_path_uri_encode(dirent, pool);

#ifndef SVN_USE_DOS_PATHS
  if (dirent[0] == '/' && dirent[1] == '\0')
    dirent = NULL; /* "file://" is the canonical form of "file:///" */

  *url = apr_pstrcat(pool, "file://", dirent, SVN_VA_NULL);
#else
  if (dirent[0] == '/')
    {
      /* Handle UNC paths //server/share -> file://server/share */
      assert(dirent[1] == '/'); /* Expect UNC, not non-absolute */

      *url = apr_pstrcat(pool, "file:", dirent, SVN_VA_NULL);
    }
  else
    {
      char *uri = apr_pstrcat(pool, "file:///", dirent, SVN_VA_NULL);
      apr_size_t len = 8 /* strlen("file:///") */ + strlen(dirent);

      /* "C:/" is a canonical dirent on Windows,
         but "file:///C:/" is not a canonical uri */
      if (uri[len-1] == '/')
        uri[len-1] = '\0';

      *url = uri;
    }
#endif

  return SVN_NO_ERROR;
}