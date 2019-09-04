#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__* ctx; } ;
struct TYPE_11__ {scalar_t__ half_closed; } ;
struct TYPE_10__ {scalar_t__ half_closed; } ;
struct TYPE_12__ {TYPE_2__ push; TYPE_1__ pull; } ;
struct TYPE_17__ {TYPE_7__ super; TYPE_3__ num_streams; } ;
typedef  TYPE_8__ h2o_http2_conn_t ;
struct TYPE_15__ {TYPE_5__* globalconf; } ;
struct TYPE_13__ {scalar_t__ max_concurrent_requests_per_connection; } ;
struct TYPE_14__ {TYPE_4__ http2; } ;

/* Variables and functions */

__attribute__((used)) static int can_run_requests(h2o_http2_conn_t *conn)
{
    return conn->num_streams.pull.half_closed + conn->num_streams.push.half_closed <
           conn->super.ctx->globalconf->http2.max_concurrent_requests_per_connection;
}