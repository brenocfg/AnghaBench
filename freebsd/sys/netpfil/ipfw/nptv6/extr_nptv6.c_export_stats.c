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
struct nptv6_cfg {int dummy; } ;
struct ipfw_nptv6_stats {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __COPY_STAT_FIELD (struct nptv6_cfg*,struct ipfw_nptv6_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  ex2in ; 
 int /*<<< orphan*/  in2ex ; 

__attribute__((used)) static void
export_stats(struct ip_fw_chain *ch, struct nptv6_cfg *cfg,
    struct ipfw_nptv6_stats *stats)
{

	__COPY_STAT_FIELD(cfg, stats, in2ex);
	__COPY_STAT_FIELD(cfg, stats, ex2in);
	__COPY_STAT_FIELD(cfg, stats, dropped);
}