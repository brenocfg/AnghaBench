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
struct ntb_softc {scalar_t__ type; int ntb_ctl; scalar_t__ peer_msix_good; } ;

/* Variables and functions */
 int ATOM_CNTL_LINK_DOWN ; 
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NTB_ATOM ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 scalar_t__ NTB_XEON ; 
 scalar_t__ _xeon_link_is_up (struct ntb_softc*) ; 

__attribute__((used)) static inline bool
link_is_up(struct ntb_softc *ntb)
{

	if (ntb->type == NTB_XEON)
		return (_xeon_link_is_up(ntb) && (ntb->peer_msix_good ||
		    !HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)));

	KASSERT(ntb->type == NTB_ATOM, ("ntb type"));
	return ((ntb->ntb_ctl & ATOM_CNTL_LINK_DOWN) == 0);
}