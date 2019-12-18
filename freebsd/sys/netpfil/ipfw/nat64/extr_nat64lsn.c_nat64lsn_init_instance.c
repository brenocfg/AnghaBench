#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nat64lsn_hosts_slist {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct nat64lsn_cfg {int hosts_hashsize; int prefix4; int pmask4; int plen4; int /*<<< orphan*/  jcallout; int /*<<< orphan*/  periodic_lock; int /*<<< orphan*/  periodic; struct nat64lsn_alias* aliases; int /*<<< orphan*/ * hosts_hash; int /*<<< orphan*/  hash_seed; TYPE_2__ base; int /*<<< orphan*/  vp; int /*<<< orphan*/  jhead; } ;
struct nat64lsn_alias {int addr; int /*<<< orphan*/  hosts; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_LOCK_INIT (struct nat64lsn_alias*) ; 
 int /*<<< orphan*/  CALLOUT_LOCK_INIT (struct nat64lsn_cfg*) ; 
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 int /*<<< orphan*/  CFG_LOCK_INIT (struct nat64lsn_cfg*) ; 
 int /*<<< orphan*/  CK_SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COUNTER_ARRAY_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_NAT64LSN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NAT64LSN_HOSTS_HSIZE ; 
 int /*<<< orphan*/  NAT64STATS ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

struct nat64lsn_cfg *
nat64lsn_init_instance(struct ip_fw_chain *ch, in_addr_t prefix, int plen)
{
	struct nat64lsn_cfg *cfg;
	struct nat64lsn_alias *alias;
	int i, naddr;

	cfg = malloc(sizeof(struct nat64lsn_cfg), M_NAT64LSN,
	    M_WAITOK | M_ZERO);

	CFG_LOCK_INIT(cfg);
	CALLOUT_LOCK_INIT(cfg);
	STAILQ_INIT(&cfg->jhead);
	cfg->vp = curvnet;
	COUNTER_ARRAY_ALLOC(cfg->base.stats.cnt, NAT64STATS, M_WAITOK);

	cfg->hash_seed = arc4random();
	cfg->hosts_hashsize = NAT64LSN_HOSTS_HSIZE;
	cfg->hosts_hash = malloc(sizeof(struct nat64lsn_hosts_slist) *
	    cfg->hosts_hashsize, M_NAT64LSN, M_WAITOK | M_ZERO);
	for (i = 0; i < cfg->hosts_hashsize; i++)
		CK_SLIST_INIT(&cfg->hosts_hash[i]);

	naddr = 1 << (32 - plen);
	cfg->prefix4 = prefix;
	cfg->pmask4 = prefix | (naddr - 1);
	cfg->plen4 = plen;
	cfg->aliases = malloc(sizeof(struct nat64lsn_alias) * naddr,
	    M_NAT64LSN, M_WAITOK | M_ZERO);
	for (i = 0; i < naddr; i++) {
		alias = &cfg->aliases[i];
		alias->addr = prefix + i; /* host byte order */
		CK_SLIST_INIT(&alias->hosts);
		ALIAS_LOCK_INIT(alias);
	}

        callout_init_mtx(&cfg->periodic, &cfg->periodic_lock, 0);
        callout_init(&cfg->jcallout, CALLOUT_MPSAFE);

	return (cfg);
}