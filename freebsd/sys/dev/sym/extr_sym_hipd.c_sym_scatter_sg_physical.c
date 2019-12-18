#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  hcb_p ;
typedef  TYPE_3__* ccb_p ;
struct TYPE_10__ {scalar_t__ ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_4__ bus_dma_segment_t ;
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_9__ {int segments; TYPE_2__ phys; } ;
struct TYPE_7__ {void* size; void* addr; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_SCATTER ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SYM_CONF_DMA_BOUNDARY ; 
 int SYM_CONF_MAX_SG ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 void* cpu_to_scr (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ rounddown2 (scalar_t__,int /*<<< orphan*/ ) ; 
 char* sym_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sym_scatter_sg_physical(hcb_p np, ccb_p cp, bus_dma_segment_t *psegs, int nsegs)
{
	u_long	ps, pe, pn;
	u_long	k;
	int s, t;

	SYM_LOCK_ASSERT(MA_OWNED);

	s  = SYM_CONF_MAX_SG - 1;
	t  = nsegs - 1;
	ps = psegs[t].ds_addr;
	pe = ps + psegs[t].ds_len;

	while (s >= 0) {
		pn = rounddown2(pe - 1, SYM_CONF_DMA_BOUNDARY);
		if (pn <= ps)
			pn = ps;
		k = pe - pn;
		if (DEBUG_FLAGS & DEBUG_SCATTER) {
			printf ("%s scatter: paddr=%lx len=%ld\n",
				sym_name(np), pn, k);
		}
		cp->phys.data[s].addr = cpu_to_scr(pn);
		cp->phys.data[s].size = cpu_to_scr(k);
		--s;
		if (pn == ps) {
			if (--t < 0)
				break;
			ps = psegs[t].ds_addr;
			pe = ps + psegs[t].ds_len;
		}
		else
			pe = pn;
	}

	cp->segments = SYM_CONF_MAX_SG - 1 - s;

	return t >= 0 ? -1 : 0;
}