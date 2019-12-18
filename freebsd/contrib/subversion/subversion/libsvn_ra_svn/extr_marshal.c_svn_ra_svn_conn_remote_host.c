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
struct TYPE_3__ {char const* remote_ip; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;

/* Variables and functions */

const char *svn_ra_svn_conn_remote_host(svn_ra_svn_conn_t *conn)
{
  return conn->remote_ip;
}