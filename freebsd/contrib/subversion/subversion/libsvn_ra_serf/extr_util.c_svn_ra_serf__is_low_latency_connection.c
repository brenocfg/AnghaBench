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
struct TYPE_3__ {scalar_t__ conn_latency; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ apr_time_from_msec (int) ; 

svn_boolean_t
svn_ra_serf__is_low_latency_connection(svn_ra_serf__session_t *session)
{
  return session->conn_latency >= 0 &&
         session->conn_latency < apr_time_from_msec(5);
}