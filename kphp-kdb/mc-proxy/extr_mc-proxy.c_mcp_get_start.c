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
struct connection {scalar_t__ pending_queries; scalar_t__ generation; } ;
struct TYPE_2__ {scalar_t__ complete_count; scalar_t__ last_complete_count; } ;

/* Variables and functions */
 TYPE_1__* MCS_DATA (struct connection*) ; 
 scalar_t__ conn_generation ; 
 scalar_t__ get_keys ; 
 scalar_t__ get_search_queries ; 
 scalar_t__ get_targets ; 

int mcp_get_start (struct connection *c) {
  get_targets = 0;
  get_search_queries = 0;
  get_keys = 0;
  c->generation = ++conn_generation;
  c->pending_queries = 0;
  MCS_DATA(c)->last_complete_count = MCS_DATA(c)->complete_count;
  MCS_DATA(c)->complete_count = 0;
  return 0;
}