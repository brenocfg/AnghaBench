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
struct TYPE_3__ {scalar_t__ current_out; scalar_t__ current_in; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;

/* Variables and functions */

void
svn_ra_svn__reset_command_io_counters(svn_ra_svn_conn_t *conn)
{
  conn->current_in = 0;
  conn->current_out = 0;
}