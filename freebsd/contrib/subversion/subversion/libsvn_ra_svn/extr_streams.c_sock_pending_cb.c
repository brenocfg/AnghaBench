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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ sock_baton_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
struct TYPE_7__ {TYPE_1__ desc; int /*<<< orphan*/  desc_type; } ;
typedef  TYPE_3__ apr_pollfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_POLL_SOCKET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  pending (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
sock_pending_cb(void *baton,
                svn_boolean_t *data_available)
{
  sock_baton_t *b = baton;
  apr_pollfd_t pfd;

  pfd.desc_type = APR_POLL_SOCKET;
  pfd.desc.s = b->sock;

  *data_available = pending(&pfd, b->pool);

  svn_pool_clear(b->pool);

  return SVN_NO_ERROR;
}