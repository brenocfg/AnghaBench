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
typedef  int u_int ;
struct ubsec_operand {int nsegs; int /*<<< orphan*/  segs; scalar_t__ mapsize; } ;
typedef  int /*<<< orphan*/  seg ;
typedef  scalar_t__ bus_size_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int UBS_MAX_SCATTER ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 scalar_t__ ubsec_debug ; 

__attribute__((used)) static void
ubsec_op_cb(void *arg, bus_dma_segment_t *seg, int nsegs, bus_size_t mapsize, int error)
{
	struct ubsec_operand *op = arg;

	KASSERT(nsegs <= UBS_MAX_SCATTER,
		("Too many DMA segments returned when mapping operand"));
#ifdef UBSEC_DEBUG
	if (ubsec_debug)
		printf("ubsec_op_cb: mapsize %u nsegs %d error %d\n",
			(u_int) mapsize, nsegs, error);
#endif
	if (error != 0)
		return;
	op->mapsize = mapsize;
	op->nsegs = nsegs;
	bcopy(seg, op->segs, nsegs * sizeof (seg[0]));
}