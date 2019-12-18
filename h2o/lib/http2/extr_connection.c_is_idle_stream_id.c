#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ max_open; } ;
struct TYPE_5__ {scalar_t__ max_open; } ;
struct TYPE_7__ {TYPE_2__ pull_stream_ids; TYPE_1__ push_stream_ids; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ h2o_http2_stream_is_push (scalar_t__) ; 

__attribute__((used)) static int is_idle_stream_id(h2o_http2_conn_t *conn, uint32_t stream_id)
{
    return (h2o_http2_stream_is_push(stream_id) ? conn->push_stream_ids.max_open : conn->pull_stream_ids.max_open) < stream_id;
}