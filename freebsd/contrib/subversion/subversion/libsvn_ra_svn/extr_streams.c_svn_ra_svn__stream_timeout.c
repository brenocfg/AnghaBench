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
struct TYPE_3__ {int /*<<< orphan*/  timeout_baton; int /*<<< orphan*/  (* timeout_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_ra_svn__stream_t ;
typedef  int /*<<< orphan*/  apr_interval_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
svn_ra_svn__stream_timeout(svn_ra_svn__stream_t *stream,
                           apr_interval_time_t interval)
{
  stream->timeout_fn(stream->timeout_baton, interval);
}