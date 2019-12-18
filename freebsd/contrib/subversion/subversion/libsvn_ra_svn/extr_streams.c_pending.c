#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  reqevents; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ apr_pollfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_POLLIN ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_poll (TYPE_1__*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t pending(apr_pollfd_t *pfd, apr_pool_t *pool)
{
  apr_status_t status;
  int n;

  pfd->p = pool;
  pfd->reqevents = APR_POLLIN;
  status = apr_poll(pfd, 1, &n, 0);
  return (status == APR_SUCCESS && n);
}