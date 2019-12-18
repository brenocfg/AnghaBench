#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_3__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; int /*<<< orphan*/  path; scalar_t__ expiration_date; scalar_t__ creation_date; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* svn_time_to_cstring (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *write_lock(svn_ra_svn_conn_t *conn,
                               apr_pool_t *pool,
                               const svn_lock_t *lock)
{
  const char *cdate, *edate;

  cdate = svn_time_to_cstring(lock->creation_date, pool);
  edate = lock->expiration_date
    ? svn_time_to_cstring(lock->expiration_date, pool) : NULL;
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "ccc(?c)c(?c)", lock->path,
                                  lock->token, lock->owner, lock->comment,
                                  cdate, edate));

  return SVN_NO_ERROR;
}