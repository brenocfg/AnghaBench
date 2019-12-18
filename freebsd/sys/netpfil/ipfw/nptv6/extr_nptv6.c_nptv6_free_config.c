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
struct nptv6_cfg {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_ARRAY_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  NPTV6STATS ; 
 int /*<<< orphan*/  free (struct nptv6_cfg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nptv6_free_config(struct nptv6_cfg *cfg)
{

	COUNTER_ARRAY_FREE(cfg->stats, NPTV6STATS);
	free(cfg, M_IPFW);
}