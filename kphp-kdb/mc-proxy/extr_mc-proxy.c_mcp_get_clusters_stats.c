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
struct mc_cluster {int port; int tot_buckets; double a_req; double a_sbytes; double a_rbytes; double a_timeouts; int /*<<< orphan*/  cluster_name; int /*<<< orphan*/  t_timeouts; int /*<<< orphan*/  t_rbytes; int /*<<< orphan*/  t_sbytes; int /*<<< orphan*/  t_req; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {int clusters_num; struct mc_cluster* Clusters; } ;

/* Variables and functions */
 TYPE_1__* CurConf ; 
 int STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* stats_buff ; 

int mcp_get_clusters_stats (struct connection *c, const char *key, int key_len) {
  int i;
  char *stats_buff_ptr = stats_buff;
  struct mc_cluster *C = CurConf->Clusters;
 
  stats_buff_ptr += sprintf (stats_buff_ptr, "Port\tBuckets\tReq*\tTX*\tRX*\tTOut*\tTot_Req\tTot_TX\tTot_RX\tTot_T/O\tName\n");
  for (i = 0; i < CurConf->clusters_num; i++, C++) {
    assert (stats_buff_ptr < stats_buff + STATS_BUFF_SIZE - 1024);
    stats_buff_ptr += sprintf (stats_buff_ptr, "%d\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%lld\t%lld\t%lld\t%lld\t%s\n",
			       C->port, C->tot_buckets,
			       C->a_req, C->a_sbytes, C->a_rbytes, C->a_timeouts,
			       C->t_req, C->t_sbytes, C->t_rbytes, C->t_timeouts,
			       C->cluster_name);
  }
  return return_one_key (c, key, stats_buff, stats_buff_ptr - stats_buff);
}