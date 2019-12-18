#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* mesh; } ;
struct worker {TYPE_2__ env; } ;
struct ub_server_stats {scalar_t__ num_queries_prefetch; scalar_t__ num_queries_missed_cache; scalar_t__ sum_query_list_size; scalar_t__ max_query_list_size; scalar_t__ num_queries_ip_ratelimited; scalar_t__ num_queries; } ;
struct TYPE_3__ {scalar_t__ stats_jostled; scalar_t__ stats_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_info (char*,int,unsigned int,double,unsigned int,unsigned int,...) ; 

void server_stats_log(struct ub_server_stats* stats, struct worker* worker,
	int threadnum)
{
	log_info("server stats for thread %d: %u queries, "
		"%u answers from cache, %u recursions, %u prefetch, %u rejected by "
		"ip ratelimiting",
		threadnum, (unsigned)stats->num_queries, 
		(unsigned)(stats->num_queries - 
			stats->num_queries_missed_cache),
		(unsigned)stats->num_queries_missed_cache,
		(unsigned)stats->num_queries_prefetch,
		(unsigned)stats->num_queries_ip_ratelimited);
	log_info("server stats for thread %d: requestlist max %u avg %g "
		"exceeded %u jostled %u", threadnum,
		(unsigned)stats->max_query_list_size,
		(stats->num_queries_missed_cache+stats->num_queries_prefetch)?
			(double)stats->sum_query_list_size/
			(double)(stats->num_queries_missed_cache+
			stats->num_queries_prefetch) : 0.0,
		(unsigned)worker->env.mesh->stats_dropped,
		(unsigned)worker->env.mesh->stats_jostled);
}