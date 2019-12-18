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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char const*) ; 

__attribute__((used)) static svn_error_t *fail(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                         const char *msg)
{
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w(c)", "failure", msg));
  return svn_error_trace(svn_ra_svn__flush(conn, pool));
}