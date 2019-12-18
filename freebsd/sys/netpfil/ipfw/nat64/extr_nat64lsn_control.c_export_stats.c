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
struct nat64lsn_cfg {int plen4; struct nat64lsn_alias* aliases; int /*<<< orphan*/  hosts_count; } ;
struct nat64lsn_alias {int /*<<< orphan*/ * icmp_pgmask; int /*<<< orphan*/  icmp_chunkmask; int /*<<< orphan*/ * udp_pgmask; int /*<<< orphan*/  udp_chunkmask; int /*<<< orphan*/ * tcp_pgmask; int /*<<< orphan*/  tcp_chunkmask; } ;
struct ipfw_nat64lsn_stats {int /*<<< orphan*/  icmpchunks; int /*<<< orphan*/  udpchunks; int /*<<< orphan*/  tcpchunks; int /*<<< orphan*/  hostcount; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISSET32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __COPY_STAT_FIELD (struct nat64lsn_cfg*,struct ipfw_nat64lsn_stats*,int /*<<< orphan*/ ) ; 
 scalar_t__ bitcount32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  ifrags ; 
 int /*<<< orphan*/  jcalls ; 
 int /*<<< orphan*/  jhostfails ; 
 int /*<<< orphan*/  jhostsreq ; 
 int /*<<< orphan*/  jmaxlen ; 
 int /*<<< orphan*/  jnomem ; 
 int /*<<< orphan*/  jportfails ; 
 int /*<<< orphan*/  jportreq ; 
 int /*<<< orphan*/  jreinjected ; 
 int /*<<< orphan*/  jrequests ; 
 int /*<<< orphan*/  nomatch4 ; 
 int /*<<< orphan*/  nomem ; 
 int /*<<< orphan*/  noproto ; 
 int /*<<< orphan*/  noroute4 ; 
 int /*<<< orphan*/  noroute6 ; 
 int /*<<< orphan*/  oerrors ; 
 int /*<<< orphan*/  ofrags ; 
 int /*<<< orphan*/  opcnt46 ; 
 int /*<<< orphan*/  opcnt64 ; 
 int /*<<< orphan*/  screated ; 
 int /*<<< orphan*/  sdeleted ; 
 int /*<<< orphan*/  spgcreated ; 
 int /*<<< orphan*/  spgdeleted ; 

__attribute__((used)) static void
export_stats(struct ip_fw_chain *ch, struct nat64lsn_cfg *cfg,
    struct ipfw_nat64lsn_stats *stats)
{
	struct nat64lsn_alias *alias;
	int i, j;

	__COPY_STAT_FIELD(cfg, stats, opcnt64);
	__COPY_STAT_FIELD(cfg, stats, opcnt46);
	__COPY_STAT_FIELD(cfg, stats, ofrags);
	__COPY_STAT_FIELD(cfg, stats, ifrags);
	__COPY_STAT_FIELD(cfg, stats, oerrors);
	__COPY_STAT_FIELD(cfg, stats, noroute4);
	__COPY_STAT_FIELD(cfg, stats, noroute6);
	__COPY_STAT_FIELD(cfg, stats, nomatch4);
	__COPY_STAT_FIELD(cfg, stats, noproto);
	__COPY_STAT_FIELD(cfg, stats, nomem);
	__COPY_STAT_FIELD(cfg, stats, dropped);

	__COPY_STAT_FIELD(cfg, stats, jcalls);
	__COPY_STAT_FIELD(cfg, stats, jrequests);
	__COPY_STAT_FIELD(cfg, stats, jhostsreq);
	__COPY_STAT_FIELD(cfg, stats, jportreq);
	__COPY_STAT_FIELD(cfg, stats, jhostfails);
	__COPY_STAT_FIELD(cfg, stats, jportfails);
	__COPY_STAT_FIELD(cfg, stats, jmaxlen);
	__COPY_STAT_FIELD(cfg, stats, jnomem);
	__COPY_STAT_FIELD(cfg, stats, jreinjected);
	__COPY_STAT_FIELD(cfg, stats, screated);
	__COPY_STAT_FIELD(cfg, stats, sdeleted);
	__COPY_STAT_FIELD(cfg, stats, spgcreated);
	__COPY_STAT_FIELD(cfg, stats, spgdeleted);

	stats->hostcount = cfg->hosts_count;
	for (i = 0; i < (1 << (32 - cfg->plen4)); i++) {
		alias = &cfg->aliases[i];
		for (j = 0; j < 32 && ISSET32(alias->tcp_chunkmask, j); j++)
			stats->tcpchunks += bitcount32(alias->tcp_pgmask[j]);
		for (j = 0; j < 32 && ISSET32(alias->udp_chunkmask, j); j++)
			stats->udpchunks += bitcount32(alias->udp_pgmask[j]);
		for (j = 0; j < 32 && ISSET32(alias->icmp_chunkmask, j); j++)
			stats->icmpchunks += bitcount32(alias->icmp_pgmask[j]);
	}
}