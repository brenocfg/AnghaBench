#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connection {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_long_query_buff ; 
 int* last_long_query_found ; 
 scalar_t__* last_long_query_time ; 
 scalar_t__* last_long_query_utime ; 
 scalar_t__ log_long_queries ; 
 size_t long_query_buff_ptr ; 
 int /*<<< orphan*/  tot_long_queries_time ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void complete_long_query (struct connection *c, int res) {
  last_long_query_time[long_query_buff_ptr] = get_utime (CLOCK_MONOTONIC) - last_long_query_utime[long_query_buff_ptr];
  tot_long_queries_time += last_long_query_time[long_query_buff_ptr];
  last_long_query_found[long_query_buff_ptr] = res;
  if (verbosity > 0 || log_long_queries) {
    kprintf ("%.6lf %d (%d) %s\n", last_long_query_time[long_query_buff_ptr], c ? c->fd : -1, res, last_long_query_buff[long_query_buff_ptr]);
  }
}