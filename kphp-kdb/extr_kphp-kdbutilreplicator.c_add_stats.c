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
struct worker_stats {scalar_t__ posinfo_packets_received; scalar_t__ posinfo_packets_not_sent; scalar_t__ posinfo_packets_sent; scalar_t__ tot_unflushed_bytes; scalar_t__ tot_read_bytes; scalar_t__ data_bytes_received; scalar_t__ data_bytes_sent; scalar_t__ unknown_packets_received; scalar_t__ rotate_packets_received; scalar_t__ rotate_packets_sent; scalar_t__ data_packets_received; scalar_t__ data_packets_sent; scalar_t__ errors_received; scalar_t__ errors_sent; scalar_t__* slave_cnt; scalar_t__ servers_sentall; scalar_t__ active_repl_clients; scalar_t__ active_repl_servers; scalar_t__ broken_slave_binlogs; scalar_t__ broken_master_binlogs; scalar_t__ conf_slave_binlogs; scalar_t__ conf_master_binlogs; } ;
struct TYPE_2__ {int /*<<< orphan*/  posinfo_packets_received; int /*<<< orphan*/  posinfo_packets_not_sent; int /*<<< orphan*/  posinfo_packets_sent; int /*<<< orphan*/  tot_unflushed_bytes; int /*<<< orphan*/  tot_read_bytes; int /*<<< orphan*/  data_bytes_received; int /*<<< orphan*/  data_bytes_sent; int /*<<< orphan*/  unknown_packets_received; int /*<<< orphan*/  rotate_packets_received; int /*<<< orphan*/  rotate_packets_sent; int /*<<< orphan*/  data_packets_received; int /*<<< orphan*/  data_packets_sent; int /*<<< orphan*/  errors_received; int /*<<< orphan*/  errors_sent; int /*<<< orphan*/ * slave_cnt; int /*<<< orphan*/  servers_sentall; int /*<<< orphan*/  active_repl_clients; int /*<<< orphan*/  active_repl_servers; int /*<<< orphan*/  broken_slave_binlogs; int /*<<< orphan*/  broken_master_binlogs; int /*<<< orphan*/  conf_slave_binlogs; int /*<<< orphan*/  conf_master_binlogs; } ;

/* Variables and functions */
 TYPE_1__ SumStats ; 

__attribute__((used)) static inline void add_stats (struct worker_stats *W) {
#define UPD(x)	SumStats.x += W->x;
  UPD (conf_master_binlogs);
  UPD (conf_slave_binlogs);
  UPD (broken_master_binlogs);
  UPD (broken_slave_binlogs);
  UPD (active_repl_servers);
  UPD (active_repl_clients);
  UPD (servers_sentall);
  UPD (slave_cnt[0]);
  UPD (slave_cnt[1]);
  UPD (slave_cnt[2]);
  UPD (slave_cnt[3]);
  UPD (errors_sent);
  UPD (errors_received);
  UPD (data_packets_sent);
  UPD (data_packets_received);
  UPD (rotate_packets_sent);
  UPD (rotate_packets_received);
  UPD (unknown_packets_received);
  UPD (data_bytes_sent);
  UPD (data_bytes_received);
  UPD (tot_read_bytes);
  UPD (tot_unflushed_bytes);
  UPD (posinfo_packets_sent);
  UPD (posinfo_packets_not_sent);
  UPD (posinfo_packets_received);
#undef UPD
}