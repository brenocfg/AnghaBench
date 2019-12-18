#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {size_t dir; } ;
struct secpolicy {scalar_t__ state; TYPE_1__ spidx; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 size_t IPSEC_DIR_INBOUND ; 
 size_t IPSEC_DIR_OUTBOUND ; 
 scalar_t__ IPSEC_SPSTATE_DEAD ; 
 scalar_t__ IPSEC_SPSTATE_IFNET ; 
 int /*<<< orphan*/  KEY_SENDUP_ALL ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secpolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SADB_X_SPDDELETE ; 
 scalar_t__ SPDCACHE_ENABLED () ; 
 int /*<<< orphan*/  SPTREE_WLOCK () ; 
 int /*<<< orphan*/  SPTREE_WUNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct secpolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_spd_size ; 
 int /*<<< orphan*/ * V_sptree_ifnet ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  idhash ; 
 int /*<<< orphan*/  key_sendup_mbuf (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* key_setdumpsp (struct secpolicy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spdcache_clear () ; 

void
key_unregister_ifnet(struct secpolicy **spp, u_int count)
{
	struct mbuf *m;
	u_int i;

	SPTREE_WLOCK();
	for (i = 0; i < count; i++) {
		IPSEC_ASSERT(spp[i]->spidx.dir == IPSEC_DIR_INBOUND ||
		    spp[i]->spidx.dir == IPSEC_DIR_OUTBOUND,
		    ("invalid direction %u", spp[i]->spidx.dir));

		if (spp[i]->state != IPSEC_SPSTATE_IFNET)
			continue;
		spp[i]->state = IPSEC_SPSTATE_DEAD;
		TAILQ_REMOVE(&V_sptree_ifnet[spp[i]->spidx.dir],
		    spp[i], chain);
		V_spd_size--;
		LIST_REMOVE(spp[i], idhash);
	}
	SPTREE_WUNLOCK();
	if (SPDCACHE_ENABLED())
		spdcache_clear();

	for (i = 0; i < count; i++) {
		m = key_setdumpsp(spp[i], SADB_X_SPDDELETE, 0, 0);
		if (m != NULL)
			key_sendup_mbuf(NULL, m, KEY_SENDUP_ALL);
	}
}