#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union engine_stats {int dummy; } engine_stats ;
struct rpc_stats {int /*<<< orphan*/  stats; int /*<<< orphan*/  id; } ;
struct connection {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats_sent; } ;
struct TYPE_5__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ID ; 
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_STATS ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ rpc_create_query (struct rpc_stats*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_stats*,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct connection*) ; 

int rpc_send_stats (struct connection *c) {    
  vkprintf (2, "rpc_send_stats: c = %p\n", c);
  struct rpc_stats *T = (struct rpc_stats *)Q;
  if (rpc_create_query (T, sizeof (struct rpc_stats), c, RPC_TYPE_STATS) < 0) {
    return -1;
  }
  T->id = NODE_ID;
  memcpy (&T->stats, STATS, sizeof (union engine_stats));
  STATS->structured.stats_sent++;
  return rpc_send_query (T, c);
}