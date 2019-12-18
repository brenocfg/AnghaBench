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
struct TYPE_3__ {scalar_t__ block_handler; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
typedef  int apr_interval_time_t ;

/* Variables and functions */

__attribute__((used)) static apr_interval_time_t
get_timeout(svn_ra_svn_conn_t *conn)
{
  return conn->block_handler ? 0 : -1;
}