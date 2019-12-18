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
struct nm_bridge {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ifp; scalar_t__ nm_mem; } ;
struct TYPE_6__ {int bdg_port; TYPE_2__ up; struct nm_bridge* na_bdg; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdg_port; struct nm_bridge* na_bdg; } ;
struct netmap_bwrap_adapter {int /*<<< orphan*/  saved_na_vp; TYPE_3__ host; TYPE_1__ up; struct netmap_adapter* hwna; } ;
struct netmap_adapter {int /*<<< orphan*/  na_flags; int /*<<< orphan*/ * na_private; int /*<<< orphan*/ * na_hostvp; int /*<<< orphan*/  na_vp; int /*<<< orphan*/ * ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAF_BUSY ; 
 int /*<<< orphan*/  netmap_adapter_put (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_bdg_detach_common (struct nm_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netmap_mem_put (scalar_t__) ; 
 int /*<<< orphan*/  nm_prdis (char*,struct netmap_adapter*) ; 

__attribute__((used)) static void
netmap_bwrap_dtor(struct netmap_adapter *na)
{
	struct netmap_bwrap_adapter *bna = (struct netmap_bwrap_adapter*)na;
	struct netmap_adapter *hwna = bna->hwna;
	struct nm_bridge *b = bna->up.na_bdg,
		*bh = bna->host.na_bdg;

	if (bna->host.up.nm_mem)
		netmap_mem_put(bna->host.up.nm_mem);

	if (b) {
		netmap_bdg_detach_common(b, bna->up.bdg_port,
			    (bh ? bna->host.bdg_port : -1));
	}

	nm_prdis("na %p", na);
	na->ifp = NULL;
	bna->host.up.ifp = NULL;
	hwna->na_vp = bna->saved_na_vp;
	hwna->na_hostvp = NULL;
	hwna->na_private = NULL;
	hwna->na_flags &= ~NAF_BUSY;
	netmap_adapter_put(hwna);

}