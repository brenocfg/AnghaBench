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
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  targ_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mcs_targ_stats (struct connection *c) {
  write_out (&c->Out, stats_buff, targ_prepare_stats (c));
  return 0;
}