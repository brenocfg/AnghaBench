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
typedef  scalar_t__ u_int ;
struct pf_state_key {int dummy; } ;
struct pf_state {int dummy; } ;
struct pf_srchash {int /*<<< orphan*/  lock; } ;
struct pf_src_node {int dummy; } ;
struct pf_keyhash {int /*<<< orphan*/  lock; } ;
struct pf_idhash {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {void* zone; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_PFHASH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PFSNODE_HIWAT ; 
 int /*<<< orphan*/  PFSTATE_HIWAT ; 
 scalar_t__ PF_HASHSIZ ; 
 size_t PF_LIMIT_SRC_NODES ; 
 size_t PF_LIMIT_STATES ; 
 scalar_t__ PF_SRCHASHSIZ ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/ * V_pf_altq_ifs_active ; 
 int /*<<< orphan*/ * V_pf_altq_ifs_inactive ; 
 int /*<<< orphan*/ * V_pf_altqs ; 
 int /*<<< orphan*/ * V_pf_altqs_active ; 
 int /*<<< orphan*/ * V_pf_altqs_inactive ; 
 int /*<<< orphan*/  V_pf_hashseed ; 
 struct pf_keyhash* V_pf_idhash ; 
 struct pf_keyhash* V_pf_keyhash ; 
 TYPE_1__* V_pf_limits ; 
 int /*<<< orphan*/  V_pf_overloadqueue ; 
 int /*<<< orphan*/  V_pf_overloadtask ; 
 int /*<<< orphan*/  V_pf_pabuf ; 
 int /*<<< orphan*/  V_pf_sendqueue ; 
 void* V_pf_sources_z ; 
 struct pf_srchash* V_pf_srchash ; 
 void* V_pf_state_key_z ; 
 void* V_pf_state_z ; 
 int /*<<< orphan*/  V_pf_unlinked_rules ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  free (struct pf_keyhash*,int /*<<< orphan*/ ) ; 
 void* mallocarray (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pf_hashmask ; 
 scalar_t__ pf_hashsize ; 
 int /*<<< orphan*/  pf_overload_task ; 
 scalar_t__ pf_srchashmask ; 
 scalar_t__ pf_srchashsize ; 
 int /*<<< orphan*/ * pf_state_key_ctor ; 
 int /*<<< orphan*/  powerof2 (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_warning (void*,char*) ; 

void
pf_initialize()
{
	struct pf_keyhash	*kh;
	struct pf_idhash	*ih;
	struct pf_srchash	*sh;
	u_int i;

	if (pf_hashsize == 0 || !powerof2(pf_hashsize))
		pf_hashsize = PF_HASHSIZ;
	if (pf_srchashsize == 0 || !powerof2(pf_srchashsize))
		pf_srchashsize = PF_SRCHASHSIZ;

	V_pf_hashseed = arc4random();

	/* States and state keys storage. */
	V_pf_state_z = uma_zcreate("pf states", sizeof(struct pf_state),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	V_pf_limits[PF_LIMIT_STATES].zone = V_pf_state_z;
	uma_zone_set_max(V_pf_state_z, PFSTATE_HIWAT);
	uma_zone_set_warning(V_pf_state_z, "PF states limit reached");

	V_pf_state_key_z = uma_zcreate("pf state keys",
	    sizeof(struct pf_state_key), pf_state_key_ctor, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

	V_pf_keyhash = mallocarray(pf_hashsize, sizeof(struct pf_keyhash),
	    M_PFHASH, M_NOWAIT | M_ZERO);
	V_pf_idhash = mallocarray(pf_hashsize, sizeof(struct pf_idhash),
	    M_PFHASH, M_NOWAIT | M_ZERO);
	if (V_pf_keyhash == NULL || V_pf_idhash == NULL) {
		printf("pf: Unable to allocate memory for "
		    "state_hashsize %lu.\n", pf_hashsize);

		free(V_pf_keyhash, M_PFHASH);
		free(V_pf_idhash, M_PFHASH);

		pf_hashsize = PF_HASHSIZ;
		V_pf_keyhash = mallocarray(pf_hashsize,
		    sizeof(struct pf_keyhash), M_PFHASH, M_WAITOK | M_ZERO);
		V_pf_idhash = mallocarray(pf_hashsize,
		    sizeof(struct pf_idhash), M_PFHASH, M_WAITOK | M_ZERO);
	}

	pf_hashmask = pf_hashsize - 1;
	for (i = 0, kh = V_pf_keyhash, ih = V_pf_idhash; i <= pf_hashmask;
	    i++, kh++, ih++) {
		mtx_init(&kh->lock, "pf_keyhash", NULL, MTX_DEF | MTX_DUPOK);
		mtx_init(&ih->lock, "pf_idhash", NULL, MTX_DEF);
	}

	/* Source nodes. */
	V_pf_sources_z = uma_zcreate("pf source nodes",
	    sizeof(struct pf_src_node), NULL, NULL, NULL, NULL, UMA_ALIGN_PTR,
	    0);
	V_pf_limits[PF_LIMIT_SRC_NODES].zone = V_pf_sources_z;
	uma_zone_set_max(V_pf_sources_z, PFSNODE_HIWAT);
	uma_zone_set_warning(V_pf_sources_z, "PF source nodes limit reached");

	V_pf_srchash = mallocarray(pf_srchashsize,
	    sizeof(struct pf_srchash), M_PFHASH, M_NOWAIT | M_ZERO);
	if (V_pf_srchash == NULL) {
		printf("pf: Unable to allocate memory for "
		    "source_hashsize %lu.\n", pf_srchashsize);

		pf_srchashsize = PF_SRCHASHSIZ;
		V_pf_srchash = mallocarray(pf_srchashsize,
		    sizeof(struct pf_srchash), M_PFHASH, M_WAITOK | M_ZERO);
	}

	pf_srchashmask = pf_srchashsize - 1;
	for (i = 0, sh = V_pf_srchash; i <= pf_srchashmask; i++, sh++)
		mtx_init(&sh->lock, "pf_srchash", NULL, MTX_DEF);

	/* ALTQ */
	TAILQ_INIT(&V_pf_altqs[0]);
	TAILQ_INIT(&V_pf_altqs[1]);
	TAILQ_INIT(&V_pf_altqs[2]);
	TAILQ_INIT(&V_pf_altqs[3]);
	TAILQ_INIT(&V_pf_pabuf);
	V_pf_altqs_active = &V_pf_altqs[0];
	V_pf_altq_ifs_active = &V_pf_altqs[1];
	V_pf_altqs_inactive = &V_pf_altqs[2];
	V_pf_altq_ifs_inactive = &V_pf_altqs[3];

	/* Send & overload+flush queues. */
	STAILQ_INIT(&V_pf_sendqueue);
	SLIST_INIT(&V_pf_overloadqueue);
	TASK_INIT(&V_pf_overloadtask, 0, pf_overload_task, curvnet);

	/* Unlinked, but may be referenced rules. */
	TAILQ_INIT(&V_pf_unlinked_rules);
}