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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_stats ; 
 int copyexec_results_prepare_stats (struct connection*) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_stats (struct connection *c) {
  cmd_stats++;
  int len = copyexec_results_prepare_stats (c);
  write_out (&c->Out, stats_buff, len);
  write_out (&c->Out, "END\r\n", 5);
  return 0;
}