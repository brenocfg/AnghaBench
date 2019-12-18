#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {TYPE_1__* repository; TYPE_2__* client_info; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  enum access_type { ____Placeholder_access_type } access_type ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {scalar_t__ tunnel_user; } ;
struct TYPE_5__ {int anon_access; int auth_access; scalar_t__ pwdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_svn__write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *send_mechs(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                               server_baton_t *b, enum access_type required,
                               svn_boolean_t needs_username)
{
  if (!needs_username && b->repository->anon_access >= required)
    SVN_ERR(svn_ra_svn__write_word(conn, pool, "ANONYMOUS"));
  if (b->client_info->tunnel_user && b->repository->auth_access >= required)
    SVN_ERR(svn_ra_svn__write_word(conn, pool, "EXTERNAL"));
  if (b->repository->pwdb && b->repository->auth_access >= required)
    SVN_ERR(svn_ra_svn__write_word(conn, pool, "CRAM-MD5"));
  return SVN_NO_ERROR;
}