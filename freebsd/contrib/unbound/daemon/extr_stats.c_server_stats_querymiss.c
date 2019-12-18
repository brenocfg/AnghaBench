#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* mesh; } ;
struct worker {TYPE_3__ env; } ;
struct ub_server_stats {long long max_query_list_size; int /*<<< orphan*/  sum_query_list_size; int /*<<< orphan*/  num_queries_missed_cache; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_5__ {TYPE_1__ all; } ;

/* Variables and functions */

void server_stats_querymiss(struct ub_server_stats* stats, struct worker* worker)
{
	stats->num_queries_missed_cache++;
	stats->sum_query_list_size += worker->env.mesh->all.count;
	if((long long)worker->env.mesh->all.count > stats->max_query_list_size)
		stats->max_query_list_size = (long long)worker->env.mesh->all.count;
}