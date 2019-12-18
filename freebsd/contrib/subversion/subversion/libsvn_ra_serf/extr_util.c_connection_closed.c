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
struct TYPE_5__ {int /*<<< orphan*/ * ssl_context; TYPE_1__* session; } ;
typedef  TYPE_2__ svn_ra_serf__connection_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ using_ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
connection_closed(svn_ra_serf__connection_t *conn,
                  apr_status_t why,
                  apr_pool_t *pool)
{
  if (why)
    {
      return svn_ra_serf__wrap_err(why, NULL);
    }

  if (conn->session->using_ssl)
    conn->ssl_context = NULL;

  return SVN_NO_ERROR;
}