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
struct xgbe_ring_desc {scalar_t__ desc3; scalar_t__ desc2; scalar_t__ desc1; scalar_t__ desc0; } ;
struct xgbe_ring_data {struct xgbe_ring_desc* rdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sy ; 

__attribute__((used)) static void xgbe_tx_desc_reset(struct xgbe_ring_data *rdata)
{
	struct xgbe_ring_desc *rdesc = rdata->rdesc;

	/* Reset the Tx descriptor
	 *   Set buffer 1 (lo) address to zero
	 *   Set buffer 1 (hi) address to zero
	 *   Reset all other control bits (IC, TTSE, B2L & B1L)
	 *   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
	 */
	rdesc->desc0 = 0;
	rdesc->desc1 = 0;
	rdesc->desc2 = 0;
	rdesc->desc3 = 0;

	dsb(sy);
}