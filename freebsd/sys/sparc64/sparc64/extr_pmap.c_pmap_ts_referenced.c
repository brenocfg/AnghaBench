#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int u_long ;
struct tte {int tte_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  tte_list; } ;
struct TYPE_6__ {int oflags; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PMAP_TS_REFERENCED_MAX ; 
 struct tte* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 struct tte* TAILQ_NEXT (struct tte*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 int TD_PV ; 
 int TD_REF ; 
 int TD_W ; 
 int VPO_UNMANAGED ; 
 int atomic_clear_long (int*,int) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tte_link ; 
 int /*<<< orphan*/  tte_list_global_lock ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_2__*) ; 

int
pmap_ts_referenced(vm_page_t m)
{
	struct tte *tpf;
	struct tte *tpn;
	struct tte *tp;
	u_long data;
	int count;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_ts_referenced: page %p is not managed", m));
	count = 0;
	rw_wlock(&tte_list_global_lock);
	if ((tp = TAILQ_FIRST(&m->md.tte_list)) != NULL) {
		tpf = tp;
		do {
			tpn = TAILQ_NEXT(tp, tte_link);
			TAILQ_REMOVE(&m->md.tte_list, tp, tte_link);
			TAILQ_INSERT_TAIL(&m->md.tte_list, tp, tte_link);
			if ((tp->tte_data & TD_PV) == 0)
				continue;
			data = atomic_clear_long(&tp->tte_data, TD_REF);
			if ((data & TD_W) != 0)
				vm_page_dirty(m);
			if ((data & TD_REF) != 0 && ++count >=
			    PMAP_TS_REFERENCED_MAX)
				break;
		} while ((tp = tpn) != NULL && tp != tpf);
	}
	rw_wunlock(&tte_list_global_lock);
	return (count);
}