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
struct secpolicy {int /*<<< orphan*/  state; int /*<<< orphan*/  id; TYPE_1__ spidx; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 size_t IPSEC_DIR_INBOUND ; 
 size_t IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  IPSEC_SPSTATE_IFNET ; 
 int /*<<< orphan*/  KEY_SENDUP_ALL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct secpolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SADB_X_SPDADD ; 
 int /*<<< orphan*/  SPHASH_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPTREE_WLOCK () ; 
 int /*<<< orphan*/  SPTREE_WUNLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct secpolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * V_sptree_ifnet ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  idhash ; 
 int /*<<< orphan*/  key_getnewspid () ; 
 int /*<<< orphan*/  key_sendup_mbuf (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* key_setdumpsp (struct secpolicy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
key_register_ifnet(struct secpolicy **spp, u_int count)
{
	struct mbuf *m;
	u_int i;

	SPTREE_WLOCK();
	/*
	 * First of try to acquire id for each SP.
	 */
	for (i = 0; i < count; i++) {
		IPSEC_ASSERT(spp[i]->spidx.dir == IPSEC_DIR_INBOUND ||
		    spp[i]->spidx.dir == IPSEC_DIR_OUTBOUND,
		    ("invalid direction %u", spp[i]->spidx.dir));

		if ((spp[i]->id = key_getnewspid()) == 0) {
			SPTREE_WUNLOCK();
			return (EAGAIN);
		}
	}
	for (i = 0; i < count; i++) {
		TAILQ_INSERT_TAIL(&V_sptree_ifnet[spp[i]->spidx.dir],
		    spp[i], chain);
		/*
		 * NOTE: despite the fact that we keep VTI SP in the
		 * separate list, SPHASH contains policies from both
		 * sources. Thus SADB_X_SPDGET will correctly return
		 * SP by id, because it uses SPHASH for lookups.
		 */
		LIST_INSERT_HEAD(SPHASH_HASH(spp[i]->id), spp[i], idhash);
		spp[i]->state = IPSEC_SPSTATE_IFNET;
	}
	SPTREE_WUNLOCK();
	/*
	 * Notify user processes about new SP.
	 */
	for (i = 0; i < count; i++) {
		m = key_setdumpsp(spp[i], SADB_X_SPDADD, 0, 0);
		if (m != NULL)
			key_sendup_mbuf(NULL, m, KEY_SENDUP_ALL);
	}
	return (0);
}