#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union nat64lsn_pgidx {int addr; int port; int proto; } ;
struct nat64lsn_pg {int dummy; } ;
struct nat64lsn_cfg {int plen4; struct nat64lsn_alias* aliases; } ;
struct nat64lsn_alias {int addr; TYPE_3__** udp; int /*<<< orphan*/ * udp_pgmask; TYPE_2__** tcp; int /*<<< orphan*/ * tcp_pgmask; TYPE_1__** icmp; int /*<<< orphan*/ * icmp_pgmask; } ;
struct TYPE_6__ {struct nat64lsn_pg** pgptr; } ;
struct TYPE_5__ {struct nat64lsn_pg** pgptr; } ;
struct TYPE_4__ {struct nat64lsn_pg** pgptr; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  ISSET32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NAT64_MIN_PORT ; 

__attribute__((used)) static struct nat64lsn_pg*
nat64lsn_get_pg_byidx(struct nat64lsn_cfg *cfg, union nat64lsn_pgidx *idx)
{
	struct nat64lsn_alias *alias;
	int pg_idx;

	alias = &cfg->aliases[idx->addr & ((1 << (32 - cfg->plen4)) - 1)];
	MPASS(alias->addr == idx->addr);

	pg_idx = (idx->port - NAT64_MIN_PORT) / 64;
	switch (idx->proto) {
	case IPPROTO_ICMP:
		if (ISSET32(alias->icmp_pgmask[pg_idx / 32], pg_idx % 32))
			return (alias->icmp[pg_idx / 32]->pgptr[pg_idx % 32]);
		break;
	case IPPROTO_TCP:
		if (ISSET32(alias->tcp_pgmask[pg_idx / 32], pg_idx % 32))
			return (alias->tcp[pg_idx / 32]->pgptr[pg_idx % 32]);
		break;
	case IPPROTO_UDP:
		if (ISSET32(alias->udp_pgmask[pg_idx / 32], pg_idx % 32))
			return (alias->udp[pg_idx / 32]->pgptr[pg_idx % 32]);
		break;
	}
	return (NULL);
}