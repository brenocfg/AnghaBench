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

/* Variables and functions */
 scalar_t__ STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  rpc_proxy_prepare_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stats_buffer ; 
 int /*<<< orphan*/  tl_store_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void store_stats (void) {
  rpc_proxy_prepare_stats (0, stats_buffer, STATS_BUFF_SIZE - 2);
  tl_store_stats (stats_buffer, 0);
}