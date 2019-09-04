#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct st_duration_stats_t {int /*<<< orphan*/  total_time; int /*<<< orphan*/  response_time; int /*<<< orphan*/  process_time; int /*<<< orphan*/  request_total_time; int /*<<< orphan*/  body_time; int /*<<< orphan*/  header_time; int /*<<< orphan*/  connect_time; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {TYPE_1__* conn; } ;
typedef  TYPE_2__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_logger_t ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  gkc_insert_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st_duration_stats_t* h2o_context_get_logger_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_body_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_connect_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_header_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_process_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_request_total_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_response_time (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_time_compute_total_time (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stat_access(h2o_logger_t *_self, h2o_req_t *req)
{
    struct st_duration_stats_t *ctx_stats = h2o_context_get_logger_context(req->conn->ctx, _self);
#define ADD_OBSERVATION(x, from, until)                                                                                            \
    do {                                                                                                                           \
        int64_t dur;                                                                                                               \
        if (h2o_time_compute_##x(req, &dur)) {                                                                                     \
            gkc_insert_value(ctx_stats->x, dur);                                                                                   \
        }                                                                                                                          \
    } while (0)

    ADD_OBSERVATION(connect_time, &req->conn->connected_at, &req->timestamps.request_begin_at);
    ADD_OBSERVATION(header_time, &req->timestamps.request_begin_at,
                    h2o_timeval_is_null(&req->timestamps.request_body_begin_at) ? &req->processed_at.at
                                                                                : &req->timestamps.request_body_begin_at);
    ADD_OBSERVATION(body_time,
                    h2o_timeval_is_null(&req->timestamps.request_body_begin_at) ? &req->processed_at.at
                                                                                : &req->timestamps.request_body_begin_at,
                    &req->processed_at.at);
    ADD_OBSERVATION(request_total_time, &req->timestamps.request_begin_at, &req->processed_at.at);
    ADD_OBSERVATION(process_time, &req->processed_at.at, &req->timestamps.response_start_at);
    ADD_OBSERVATION(response_time, &req->timestamps.response_start_at, &req->timestamps.response_end_at);
    ADD_OBSERVATION(total_time, &req->timestamps.request_begin_at, &req->timestamps.response_end_at);
#undef ADD_OBSERVATION
}