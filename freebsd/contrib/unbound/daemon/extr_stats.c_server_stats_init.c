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
struct ub_server_stats {int /*<<< orphan*/  extended; } ;
struct config_file {int /*<<< orphan*/  stat_extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ub_server_stats*,int /*<<< orphan*/ ,int) ; 

void server_stats_init(struct ub_server_stats* stats, struct config_file* cfg)
{
	memset(stats, 0, sizeof(*stats));
	stats->extended = cfg->stat_extended;
}