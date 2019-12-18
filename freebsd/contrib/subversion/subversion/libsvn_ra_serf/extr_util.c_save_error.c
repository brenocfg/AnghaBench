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
struct TYPE_5__ {TYPE_2__* pending_error; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  apr_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
save_error(svn_ra_serf__session_t *session,
           svn_error_t *err)
{
  if (err || session->pending_error)
    {
      session->pending_error = svn_error_compose_create(
                                  session->pending_error,
                                  err);
      return session->pending_error->apr_err;
    }

  return APR_SUCCESS;
}