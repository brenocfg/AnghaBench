#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  stream; void* block_baton; int /*<<< orphan*/  block_handler; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  ra_svn_block_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_ra_svn__stream_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
svn_ra_svn__set_block_handler(svn_ra_svn_conn_t *conn,
                              ra_svn_block_handler_t handler,
                              void *baton)
{
  conn->block_handler = handler;
  conn->block_baton = baton;
  svn_ra_svn__stream_timeout(conn->stream, get_timeout(conn));
}