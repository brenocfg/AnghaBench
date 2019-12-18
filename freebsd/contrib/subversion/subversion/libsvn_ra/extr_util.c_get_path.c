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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* _ (char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
get_path(const char *path_or_url,
         svn_ra_session_t *ra_session,
         apr_pool_t *pool)
{
  if (path_or_url == NULL)
    {
      svn_error_t *err = svn_ra_get_session_url(ra_session, &path_or_url,
                                                pool);
      if (err)
        {
          /* The SVN_ERR_UNSUPPORTED_FEATURE error in the caller is more
             important, so dummy up the session's URL and chuck this error. */
          svn_error_clear(err);
          return _("<repository>");
        }
    }
  return path_or_url;
}