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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int getspi_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQHASH_NHASH ; 
 int /*<<< orphan*/  ACQ_LOCK_INIT () ; 
 int IPSEC_DIR_MAX ; 
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_IPSEC_SA ; 
 int /*<<< orphan*/  M_IPSEC_SAH ; 
 int /*<<< orphan*/  M_IPSEC_SAQ ; 
 int /*<<< orphan*/  M_IPSEC_SP ; 
 int /*<<< orphan*/  REGTREE_LOCK_INIT () ; 
 int SADB_SATYPE_MAX ; 
 int /*<<< orphan*/  SAHHASH_NHASH ; 
 int /*<<< orphan*/  SAHTREE_LOCK_INIT () ; 
 int /*<<< orphan*/  SAVHASH_NHASH ; 
 int /*<<< orphan*/  SPACQ_LOCK_INIT () ; 
 int /*<<< orphan*/  SPHASH_NHASH ; 
 int /*<<< orphan*/  SPTREE_LOCK_INIT () ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  UMA_ZONE_PCPU ; 
 int /*<<< orphan*/  V_acqaddrhash_mask ; 
 void* V_acqaddrhashtbl ; 
 int /*<<< orphan*/  V_acqseqhash_mask ; 
 void* V_acqseqhashtbl ; 
 int /*<<< orphan*/  V_acqtree ; 
 int /*<<< orphan*/  V_key_lft_zone ; 
 int /*<<< orphan*/ * V_regtree ; 
 int /*<<< orphan*/  V_sahaddrhash_mask ; 
 void* V_sahaddrhashtbl ; 
 int /*<<< orphan*/  V_sahtree ; 
 int /*<<< orphan*/  V_savhash_mask ; 
 void* V_savhashtbl ; 
 int /*<<< orphan*/  V_spacqtree ; 
 int /*<<< orphan*/  V_sphash_mask ; 
 void* V_sphashtbl ; 
 int /*<<< orphan*/ * V_sptree ; 
 int /*<<< orphan*/ * V_sptree_ifnet ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curvnet ; 
 void* hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  key_timehandler ; 
 int /*<<< orphan*/  key_timer ; 
 TYPE_1__ keystat ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  spdcache_init () ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
key_init(void)
{
	int i;

	for (i = 0; i < IPSEC_DIR_MAX; i++) {
		TAILQ_INIT(&V_sptree[i]);
		TAILQ_INIT(&V_sptree_ifnet[i]);
	}

	V_key_lft_zone = uma_zcreate("IPsec SA lft_c",
	    sizeof(uint64_t) * 2, NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, UMA_ZONE_PCPU);

	TAILQ_INIT(&V_sahtree);
	V_sphashtbl = hashinit(SPHASH_NHASH, M_IPSEC_SP, &V_sphash_mask);
	V_savhashtbl = hashinit(SAVHASH_NHASH, M_IPSEC_SA, &V_savhash_mask);
	V_sahaddrhashtbl = hashinit(SAHHASH_NHASH, M_IPSEC_SAH,
	    &V_sahaddrhash_mask);
	V_acqaddrhashtbl = hashinit(ACQHASH_NHASH, M_IPSEC_SAQ,
	    &V_acqaddrhash_mask);
	V_acqseqhashtbl = hashinit(ACQHASH_NHASH, M_IPSEC_SAQ,
	    &V_acqseqhash_mask);

	spdcache_init();

	for (i = 0; i <= SADB_SATYPE_MAX; i++)
		LIST_INIT(&V_regtree[i]);

	LIST_INIT(&V_acqtree);
	LIST_INIT(&V_spacqtree);

	if (!IS_DEFAULT_VNET(curvnet))
		return;

	SPTREE_LOCK_INIT();
	REGTREE_LOCK_INIT();
	SAHTREE_LOCK_INIT();
	ACQ_LOCK_INIT();
	SPACQ_LOCK_INIT();

#ifndef IPSEC_DEBUG2
	callout_init(&key_timer, 1);
	callout_reset(&key_timer, hz, key_timehandler, NULL);
#endif /*IPSEC_DEBUG2*/

	/* initialize key statistics */
	keystat.getspi_count = 1;

	if (bootverbose)
		printf("IPsec: Initialized Security Association Processing.\n");
}