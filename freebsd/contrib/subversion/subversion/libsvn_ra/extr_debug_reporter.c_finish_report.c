#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct report_baton {int /*<<< orphan*/  wrapped_report_baton; TYPE_1__* wrapped_reporter; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* finish_report ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
finish_report(void *report_baton,
              apr_pool_t *pool)
{
  struct report_baton *rb = report_baton;
  SVN_ERR(svn_stream_puts(rb->out, "finish_report()\n"));
  SVN_ERR(rb->wrapped_reporter->finish_report(rb->wrapped_report_baton, pool));
  return SVN_NO_ERROR;
}