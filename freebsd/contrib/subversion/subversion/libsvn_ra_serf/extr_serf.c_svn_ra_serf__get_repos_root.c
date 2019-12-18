#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_6__ {char* repos_root_str; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_repos_root(svn_ra_session_t *ra_session,
                            const char **url,
                            apr_pool_t *pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;

  if (!session->repos_root_str)
    {
      const char *vcc_url;
      SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session, pool));
    }

  *url = session->repos_root_str;
  return SVN_NO_ERROR;
}