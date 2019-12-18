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
struct nat64stl_cfg {int dummy; } ;
struct ipfw_nat64stl_stats {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __COPY_STAT_FIELD (struct nat64stl_cfg*,struct ipfw_nat64stl_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  ifrags ; 
 int /*<<< orphan*/  nomem ; 
 int /*<<< orphan*/  noproto ; 
 int /*<<< orphan*/  noroute4 ; 
 int /*<<< orphan*/  noroute6 ; 
 int /*<<< orphan*/  oerrors ; 
 int /*<<< orphan*/  ofrags ; 
 int /*<<< orphan*/  opcnt46 ; 
 int /*<<< orphan*/  opcnt64 ; 

__attribute__((used)) static void
export_stats(struct ip_fw_chain *ch, struct nat64stl_cfg *cfg,
    struct ipfw_nat64stl_stats *stats)
{

	__COPY_STAT_FIELD(cfg, stats, opcnt64);
	__COPY_STAT_FIELD(cfg, stats, opcnt46);
	__COPY_STAT_FIELD(cfg, stats, ofrags);
	__COPY_STAT_FIELD(cfg, stats, ifrags);
	__COPY_STAT_FIELD(cfg, stats, oerrors);
	__COPY_STAT_FIELD(cfg, stats, noroute4);
	__COPY_STAT_FIELD(cfg, stats, noroute6);
	__COPY_STAT_FIELD(cfg, stats, noproto);
	__COPY_STAT_FIELD(cfg, stats, nomem);
	__COPY_STAT_FIELD(cfg, stats, dropped);
}