#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DO_AUTH (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__**,char const**) ; 

__attribute__((used)) static svn_error_t *handle_auth_request(svn_ra_svn__session_baton_t *sess,
                                        apr_pool_t *pool)
{
  svn_ra_svn_conn_t *conn = sess->conn;
  svn_ra_svn__list_t *mechlist;
  const char *realm;

  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, "lc", &mechlist, &realm));
  if (mechlist->nelts == 0)
    return SVN_NO_ERROR;
  return DO_AUTH(sess, mechlist, realm, pool);
}