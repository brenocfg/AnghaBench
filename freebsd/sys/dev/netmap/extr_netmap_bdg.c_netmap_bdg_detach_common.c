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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtor ) (int /*<<< orphan*/ *) ;} ;
struct nm_bridge {int bdg_active_ports; int* tmp_bdg_port_index; int* bdg_port_index; int /*<<< orphan*/ ** bdg_ports; TYPE_1__ bdg_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDG_WLOCK (struct nm_bridge*) ; 
 int /*<<< orphan*/  BDG_WUNLOCK (struct nm_bridge*) ; 
 int NM_DEBUG_BDG ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  netmap_bdg_free (struct nm_bridge*) ; 
 int netmap_debug ; 
 int /*<<< orphan*/  nm_prdis (char*,int,...) ; 
 int /*<<< orphan*/  nm_prerr (char*,int,int) ; 
 int /*<<< orphan*/  nm_prinf (char*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
netmap_bdg_detach_common(struct nm_bridge *b, int hw, int sw)
{
	int s_hw = hw, s_sw = sw;
	int i, lim =b->bdg_active_ports;
	uint32_t *tmp = b->tmp_bdg_port_index;

	/*
	New algorithm:
	make a copy of bdg_port_index;
	lookup NA(ifp)->bdg_port and SWNA(ifp)->bdg_port
	in the array of bdg_port_index, replacing them with
	entries from the bottom of the array;
	decrement bdg_active_ports;
	acquire BDG_WLOCK() and copy back the array.
	 */

	if (netmap_debug & NM_DEBUG_BDG)
		nm_prinf("detach %d and %d (lim %d)", hw, sw, lim);
	/* make a copy of the list of active ports, update it,
	 * and then copy back within BDG_WLOCK().
	 */
	memcpy(b->tmp_bdg_port_index, b->bdg_port_index, sizeof(b->tmp_bdg_port_index));
	for (i = 0; (hw >= 0 || sw >= 0) && i < lim; ) {
		if (hw >= 0 && tmp[i] == hw) {
			nm_prdis("detach hw %d at %d", hw, i);
			lim--; /* point to last active port */
			tmp[i] = tmp[lim]; /* swap with i */
			tmp[lim] = hw;	/* now this is inactive */
			hw = -1;
		} else if (sw >= 0 && tmp[i] == sw) {
			nm_prdis("detach sw %d at %d", sw, i);
			lim--;
			tmp[i] = tmp[lim];
			tmp[lim] = sw;
			sw = -1;
		} else {
			i++;
		}
	}
	if (hw >= 0 || sw >= 0) {
		nm_prerr("delete failed hw %d sw %d, should panic...", hw, sw);
	}

	BDG_WLOCK(b);
	if (b->bdg_ops.dtor)
		b->bdg_ops.dtor(b->bdg_ports[s_hw]);
	b->bdg_ports[s_hw] = NULL;
	if (s_sw >= 0) {
		b->bdg_ports[s_sw] = NULL;
	}
	memcpy(b->bdg_port_index, b->tmp_bdg_port_index, sizeof(b->tmp_bdg_port_index));
	b->bdg_active_ports = lim;
	BDG_WUNLOCK(b);

	nm_prdis("now %d active ports", lim);
	netmap_bdg_free(b);
}