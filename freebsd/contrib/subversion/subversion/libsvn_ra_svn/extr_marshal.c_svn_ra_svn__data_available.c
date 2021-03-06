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
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_ra_svn__stream_data_available (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_svn__data_available(svn_ra_svn_conn_t *conn,
                                       svn_boolean_t *data_available)
{
  return svn_ra_svn__stream_data_available(conn->stream, data_available);
}