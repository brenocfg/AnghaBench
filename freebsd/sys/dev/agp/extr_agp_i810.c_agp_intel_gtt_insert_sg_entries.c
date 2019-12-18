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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ u_int ;
struct sglist {scalar_t__ sg_nseg; TYPE_1__* sg_segs; } ;
struct agp_i810_softc {TYPE_3__* match; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* read_gtt_pte ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* install_gtt_pte ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_4__ {size_t ss_len; int /*<<< orphan*/  ss_paddr; } ;

/* Variables and functions */
 scalar_t__ AGP_PAGE_SIZE ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

void
agp_intel_gtt_insert_sg_entries(device_t dev, struct sglist *sg_list,
    u_int first_entry, u_int flags)
{
	struct agp_i810_softc *sc;
	vm_paddr_t spaddr;
	size_t slen;
	u_int i, j;

	sc = device_get_softc(dev);
	for (i = j = 0; j < sg_list->sg_nseg; j++) {
		spaddr = sg_list->sg_segs[i].ss_paddr;
		slen = sg_list->sg_segs[i].ss_len;
		for (; slen > 0; i++) {
			sc->match->driver->install_gtt_pte(dev, first_entry + i,
			    spaddr, flags);
			spaddr += AGP_PAGE_SIZE;
			slen -= AGP_PAGE_SIZE;
		}
	}
	sc->match->driver->read_gtt_pte(dev, first_entry + i - 1);
}