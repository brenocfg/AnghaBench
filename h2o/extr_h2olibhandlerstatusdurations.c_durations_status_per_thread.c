#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_duration_stats_t {int /*<<< orphan*/  total_time; int /*<<< orphan*/  response_time; int /*<<< orphan*/  process_time; int /*<<< orphan*/  request_total_time; int /*<<< orphan*/  body_time; int /*<<< orphan*/  header_time; int /*<<< orphan*/  connect_time; } ;
struct TYPE_2__ {struct gkc_summary* total_time; struct gkc_summary* response_time; struct gkc_summary* process_time; struct gkc_summary* request_total_time; struct gkc_summary* body_time; struct gkc_summary* header_time; struct gkc_summary* connect_time; } ;
struct st_duration_agg_stats_t {int /*<<< orphan*/  mutex; TYPE_1__ stats; } ;
struct gkc_summary {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_context_t ;

/* Variables and functions */
 scalar_t__ durations_logger ; 
 struct gkc_summary* gkc_combine (struct gkc_summary*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gkc_summary_free (struct gkc_summary*) ; 
 struct st_duration_stats_t* h2o_context_get_logger_context (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void durations_status_per_thread(void *priv, h2o_context_t *ctx)
{
    struct st_duration_agg_stats_t *agg_stats = priv;
    if (durations_logger) {
        struct st_duration_stats_t *ctx_stats = h2o_context_get_logger_context(ctx, durations_logger);
        pthread_mutex_lock(&agg_stats->mutex);
#define ADD_DURATION(x)                                                                                                            \
    do {                                                                                                                           \
        struct gkc_summary *tmp;                                                                                                   \
        tmp = gkc_combine(agg_stats->stats.x, ctx_stats->x);                                                                       \
        gkc_summary_free(agg_stats->stats.x);                                                                                      \
        agg_stats->stats.x = tmp;                                                                                                  \
    } while (0)
        ADD_DURATION(connect_time);
        ADD_DURATION(header_time);
        ADD_DURATION(body_time);
        ADD_DURATION(request_total_time);
        ADD_DURATION(process_time);
        ADD_DURATION(response_time);
        ADD_DURATION(total_time);
#undef ADD_DURATION
        pthread_mutex_unlock(&agg_stats->mutex);
    }
}