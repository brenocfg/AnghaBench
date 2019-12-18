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
struct TYPE_2__ {int /*<<< orphan*/  entries; } ;
struct st_duration_stats_t {TYPE_1__ evloop_latency_nanosec; int /*<<< orphan*/  total_time; int /*<<< orphan*/  response_time; int /*<<< orphan*/  process_time; int /*<<< orphan*/  request_total_time; int /*<<< orphan*/  body_time; int /*<<< orphan*/  header_time; int /*<<< orphan*/  connect_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gkc_summary_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void duration_stats_free(struct st_duration_stats_t *stats)
{
    gkc_summary_free(stats->connect_time);
    gkc_summary_free(stats->header_time);
    gkc_summary_free(stats->body_time);
    gkc_summary_free(stats->request_total_time);
    gkc_summary_free(stats->process_time);
    gkc_summary_free(stats->response_time);
    gkc_summary_free(stats->total_time);
    free(stats->evloop_latency_nanosec.entries);
}