#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* repos_root; } ;
typedef  TYPE_2__ svn_ra_svn_conn_t ;
struct TYPE_10__ {TYPE_2__* conn; TYPE_4__* parent; } ;
typedef  TYPE_3__ svn_ra_svn__session_baton_t ;
struct TYPE_11__ {int /*<<< orphan*/  path; int /*<<< orphan*/  client_url; TYPE_1__* server_url; } ;
typedef  TYPE_4__ svn_ra_svn__parent_t ;
struct TYPE_12__ {TYPE_3__* priv; } ;
typedef  TYPE_5__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  reparent_server (TYPE_5__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (int /*<<< orphan*/ ) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_reparent(svn_ra_session_t *ra_session,
                                    const char *url,
                                    apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = ra_session->priv;
  svn_ra_svn__parent_t *parent = sess->parent;
  svn_ra_svn_conn_t *conn = sess->conn;
  const char *path;

  /* Eliminate reparent requests if they are to a sub-path of the
     server's current parent path. */
  path = svn_uri_skip_ancestor(parent->server_url->data, url, pool);
  if (!path)
    {
      /* Send the request to the server.

         If within the same repository, reparent to the repo root
         because this will maximize the chance to turn future reparent
         requests into a client-side update of the rel path. */
      path = conn->repos_root
           ? svn_uri_skip_ancestor(conn->repos_root, url, pool)
           : NULL;

      if (path)
        SVN_ERR(reparent_server(ra_session, conn->repos_root, pool));
      else
        SVN_ERR(reparent_server(ra_session, url, pool));
    }

  /* Update the local PARENT information.
     PARENT.SERVER_BASE_URL is already up-to-date. */
  svn_stringbuf_set(parent->client_url, url);
  if (path)
    svn_stringbuf_set(parent->path, path);
  else
    svn_stringbuf_setempty(parent->path);

  return SVN_NO_ERROR;
}