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
struct TYPE_4__ {scalar_t__ dns_udp_max_response_bytes; scalar_t__ dns_tcp_max_response_bytes; scalar_t__ workers_max_idle_percent; scalar_t__ workers_max_recent_idle_percent; scalar_t__ workers_recent_idle_percent; scalar_t__ workers_average_idle_percent; scalar_t__ refused_by_remote_ip_queries; scalar_t__ rcode_refused_queries; scalar_t__ rcode_not_implemented_queries; scalar_t__ rcode_name_error_queries; scalar_t__ rcode_server_failure_queries; scalar_t__ rcode_format_queries; scalar_t__ rcode_no_error_queries; scalar_t__ dns_tcp_connections; scalar_t__ dns_truncated_responses; scalar_t__ dns_tcp_response_bytes; scalar_t__ dns_tcp_query_bytes; scalar_t__ dns_tcp_skipped_long_queries; scalar_t__ dns_tcp_bad_parse_queries; scalar_t__ dns_tcp_bad_act_queries; scalar_t__ dns_tcp_queries; scalar_t__ dns_udp_response_bytes; scalar_t__ dns_udp_query_bytes; scalar_t__ dns_udp_skipped_long_queries; scalar_t__ dns_udp_bad_parse_queries; scalar_t__ dns_udp_bad_act_queries; scalar_t__ dns_udp_queries; } ;
typedef  TYPE_1__ worker_stats_t ;

/* Variables and functions */

void update_stats (worker_stats_t *Sum, worker_stats_t *W) {
#define ADD(x) Sum->x += W->x
#define MAX(x) if (Sum->x < W->x) Sum->x = W->x
  ADD(dns_udp_queries);
  ADD(dns_udp_bad_act_queries);
  ADD(dns_udp_bad_parse_queries);
  ADD(dns_udp_skipped_long_queries);
  ADD(dns_udp_query_bytes);
  ADD(dns_udp_response_bytes);
  ADD(dns_tcp_queries);
  ADD(dns_tcp_bad_act_queries);
  ADD(dns_tcp_bad_parse_queries);
  ADD(dns_tcp_skipped_long_queries);
  ADD(dns_tcp_query_bytes);
  ADD(dns_tcp_response_bytes);
  ADD(dns_truncated_responses);
  MAX(dns_udp_max_response_bytes);
  MAX(dns_tcp_max_response_bytes);
  ADD(dns_tcp_connections);

  ADD(rcode_no_error_queries);
  ADD(rcode_format_queries);
  ADD(rcode_server_failure_queries);
  ADD(rcode_name_error_queries);
  ADD(rcode_not_implemented_queries);
  ADD(rcode_refused_queries);
  ADD(refused_by_remote_ip_queries);

  ADD(workers_average_idle_percent);
  ADD(workers_recent_idle_percent);
  MAX(workers_max_idle_percent);
  MAX(workers_max_recent_idle_percent);

#undef ADD
#undef MAX
}