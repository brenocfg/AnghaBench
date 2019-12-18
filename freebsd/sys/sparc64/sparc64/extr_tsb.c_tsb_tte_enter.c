#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;
struct tte {int tte_data; int /*<<< orphan*/  tte_vpn; } ;
typedef  TYPE_4__* pmap_t ;
struct TYPE_16__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_19__ {TYPE_1__ pm_stats; } ;
struct TYPE_17__ {int /*<<< orphan*/  tte_list; } ;
struct TYPE_18__ {int flags; int oflags; TYPE_2__ md; int /*<<< orphan*/  pindex; TYPE_14__* object; } ;
struct TYPE_15__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ DCACHE_COLOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 int TD_CP ; 
 int TD_CV ; 
 int TD_E ; 
 int TD_FAKE ; 
 int TD_PV ; 
 int TD_REF ; 
 int TD_V ; 
 int TSB_BUCKET_SIZE ; 
 int /*<<< orphan*/  TTE_GET_VA (struct tte*) ; 
 int /*<<< orphan*/  TV_VPN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 int VPO_UNMANAGED ; 
 TYPE_4__* kernel_pmap ; 
 scalar_t__ pmap_cache_enter (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove_tte (TYPE_4__*,int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 int rd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick ; 
 int /*<<< orphan*/  tlb_page_demap (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct tte* tsb_kvtotte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsb_nenter_k ; 
 int /*<<< orphan*/  tsb_nenter_k_oc ; 
 int /*<<< orphan*/  tsb_nenter_u ; 
 int /*<<< orphan*/  tsb_nenter_u_oc ; 
 int /*<<< orphan*/  tsb_nrepl ; 
 struct tte* tsb_vtobucket (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tte_link ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

struct tte *
tsb_tte_enter(pmap_t pm, vm_page_t m, vm_offset_t va, u_long sz, u_long data)
{
	struct tte *bucket;
	struct tte *rtp;
	struct tte *tp;
	vm_offset_t ova;
	int b0;
	int i;

	if (DCACHE_COLOR(VM_PAGE_TO_PHYS(m)) != DCACHE_COLOR(va)) {
		CTR5(KTR_SPARE2,
	"tsb_tte_enter: off colour va=%#lx pa=%#lx o=%p ot=%d pi=%#lx",
		    va, VM_PAGE_TO_PHYS(m), m->object,
		    m->object ? m->object->type : -1,
		    m->pindex);
		if (pm == kernel_pmap)
			PMAP_STATS_INC(tsb_nenter_k_oc);
		else
			PMAP_STATS_INC(tsb_nenter_u_oc);
	}

	rw_assert(&tte_list_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pm, MA_OWNED);
	if (pm == kernel_pmap) {
		PMAP_STATS_INC(tsb_nenter_k);
		tp = tsb_kvtotte(va);
		KASSERT((tp->tte_data & TD_V) == 0,
		    ("tsb_tte_enter: replacing valid kernel mapping"));
		goto enter;
	}
	PMAP_STATS_INC(tsb_nenter_u);

	bucket = tsb_vtobucket(pm, sz, va);

	tp = NULL;
	rtp = NULL;
	b0 = rd(tick) & (TSB_BUCKET_SIZE - 1);
	i = b0;
	do {
		if ((bucket[i].tte_data & TD_V) == 0) {
			tp = &bucket[i];
			break;
		}
		if (tp == NULL) {
			if ((bucket[i].tte_data & TD_REF) == 0)
				tp = &bucket[i];
			else if (rtp == NULL)
				rtp = &bucket[i];
		}
	} while ((i = (i + 1) & (TSB_BUCKET_SIZE - 1)) != b0);

	if (tp == NULL)
		tp = rtp;
	if ((tp->tte_data & TD_V) != 0) {
		PMAP_STATS_INC(tsb_nrepl);
		ova = TTE_GET_VA(tp);
		pmap_remove_tte(pm, NULL, tp, ova);
		tlb_page_demap(pm, ova);
	}

enter:
	if ((m->flags & PG_FICTITIOUS) == 0) {
		data |= TD_CP;
		if ((m->oflags & VPO_UNMANAGED) == 0) {
			pm->pm_stats.resident_count++;
			data |= TD_PV;
		}
		if (pmap_cache_enter(m, va) != 0)
			data |= TD_CV;
		TAILQ_INSERT_TAIL(&m->md.tte_list, tp, tte_link);
	} else
		data |= TD_FAKE | TD_E;

	tp->tte_vpn = TV_VPN(va, sz);
	tp->tte_data = data;

	return (tp);
}