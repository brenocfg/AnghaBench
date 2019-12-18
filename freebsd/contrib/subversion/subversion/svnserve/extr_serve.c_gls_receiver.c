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
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; } ;
typedef  TYPE_1__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *gls_receiver(svn_location_segment_t *segment,
                                 void *baton,
                                 apr_pool_t *pool)
{
  svn_ra_svn_conn_t *conn = baton;
  return svn_ra_svn__write_tuple(conn, pool, "rr(?c)",
                                 segment->range_start,
                                 segment->range_end,
                                 segment->path);
}