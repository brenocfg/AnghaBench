#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_5__ {int /*<<< orphan*/  fs_path; int /*<<< orphan*/  repos_url; } ;
typedef  TYPE_2__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_uri_skip_ancestor (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__reparent(svn_ra_session_t *session,
                       const char *url,
                       apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;
  const char *relpath = svn_uri_skip_ancestor(sess->repos_url, url, pool);

  /* If the new URL isn't the same as our repository root URL, then
     let's ensure that it's some child of it. */
  if (! relpath)
    return svn_error_createf
      (SVN_ERR_RA_ILLEGAL_URL, NULL,
       _("URL '%s' is not a child of the session's repository root "
         "URL '%s'"), url, sess->repos_url);

  /* Update our FS_PATH sess member to point to our new
     relative-URL-turned-absolute-filesystem-path. */
  svn_stringbuf_set(sess->fs_path,
                    svn_fspath__canonicalize(relpath, pool));

  return SVN_NO_ERROR;
}