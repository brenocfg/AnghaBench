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
struct ntb_softc {scalar_t__ b2b_mw_idx; scalar_t__ b2b_off; scalar_t__ msix_mw_idx; } ;

/* Variables and functions */
 scalar_t__ B2B_MW_DISABLED ; 

__attribute__((used)) static unsigned
intel_ntb_user_mw_to_idx(struct ntb_softc *ntb, unsigned uidx)
{

	if ((ntb->b2b_mw_idx != B2B_MW_DISABLED && ntb->b2b_off == 0 &&
	    uidx >= ntb->b2b_mw_idx) ||
	    (ntb->msix_mw_idx != B2B_MW_DISABLED && uidx >= ntb->msix_mw_idx))
		uidx++;
	if ((ntb->b2b_mw_idx != B2B_MW_DISABLED && ntb->b2b_off == 0 &&
	    uidx >= ntb->b2b_mw_idx) &&
	    (ntb->msix_mw_idx != B2B_MW_DISABLED && uidx >= ntb->msix_mw_idx))
		uidx++;
	return (uidx);
}