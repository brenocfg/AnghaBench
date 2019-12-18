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
typedef  int uint32_t ;
struct hhook_head {uintptr_t hhh_vid; int /*<<< orphan*/  hhh_refcount; int /*<<< orphan*/  hhh_flags; int /*<<< orphan*/  hhh_hooks; scalar_t__ hhh_nhooks; void* hhh_id; void* hhh_type; } ;
typedef  void* int32_t ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HHHLIST_LOCK () ; 
 int /*<<< orphan*/  HHHLIST_UNLOCK () ; 
 int /*<<< orphan*/  HHH_ISINVNET ; 
 int /*<<< orphan*/  HHH_LOCK_INIT (struct hhook_head*) ; 
 int HHOOK_HEADISINVNET ; 
 int HHOOK_WAITOK ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hhook_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_HHOOK ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_hhook_vhead_list ; 
 int /*<<< orphan*/ * curvnet ; 
 int /*<<< orphan*/  hhh_next ; 
 int /*<<< orphan*/  hhh_vnext ; 
 struct hhook_head* hhook_head_get (void*,void*) ; 
 int /*<<< orphan*/  hhook_head_list ; 
 int /*<<< orphan*/  hhook_head_release (struct hhook_head*) ; 
 int /*<<< orphan*/  khelp_new_hhook_registered (struct hhook_head*,int) ; 
 struct hhook_head* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_hhookheads ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 

int
hhook_head_register(int32_t hhook_type, int32_t hhook_id, struct hhook_head **hhh,
    uint32_t flags)
{
	struct hhook_head *tmphhh;

	tmphhh = hhook_head_get(hhook_type, hhook_id);

	if (tmphhh != NULL) {
		/* Hook point previously registered. */
		hhook_head_release(tmphhh);
		return (EEXIST);
	}

	tmphhh = malloc(sizeof(struct hhook_head), M_HHOOK,
	    M_ZERO | ((flags & HHOOK_WAITOK) ? M_WAITOK : M_NOWAIT));

	if (tmphhh == NULL)
		return (ENOMEM);

	tmphhh->hhh_type = hhook_type;
	tmphhh->hhh_id = hhook_id;
	tmphhh->hhh_nhooks = 0;
	STAILQ_INIT(&tmphhh->hhh_hooks);
	HHH_LOCK_INIT(tmphhh);
	refcount_init(&tmphhh->hhh_refcount, 1);

	HHHLIST_LOCK();
	if (flags & HHOOK_HEADISINVNET) {
		tmphhh->hhh_flags |= HHH_ISINVNET;
#ifdef VIMAGE
		KASSERT(curvnet != NULL, ("curvnet is NULL"));
		tmphhh->hhh_vid = (uintptr_t)curvnet;
		LIST_INSERT_HEAD(&V_hhook_vhead_list, tmphhh, hhh_vnext);
#endif
	}
	LIST_INSERT_HEAD(&hhook_head_list, tmphhh, hhh_next);
	n_hhookheads++;
	HHHLIST_UNLOCK();

	khelp_new_hhook_registered(tmphhh, flags);

	if (hhh != NULL)
		*hhh = tmphhh;
	else
		refcount_release(&tmphhh->hhh_refcount);

	return (0);
}