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
struct TYPE_3__ {scalar_t__ scheduled; } ;
typedef  TYPE_1__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  svn_ra_serf__unschedule_handler (TYPE_1__*) ; 

__attribute__((used)) static apr_status_t
handler_cleanup(void *baton)
{
  svn_ra_serf__handler_t *handler = baton;
  if (handler->scheduled)
    {
      svn_ra_serf__unschedule_handler(handler);
    }

  return APR_SUCCESS;
}