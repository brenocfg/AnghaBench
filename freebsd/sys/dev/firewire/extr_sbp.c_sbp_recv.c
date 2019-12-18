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
struct sbp_softc {int dummy; } ;
struct fw_xfer {scalar_t__ sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_LOCK (struct sbp_softc*) ; 
 int /*<<< orphan*/  SBP_UNLOCK (struct sbp_softc*) ; 
 int /*<<< orphan*/  sbp_recv1 (struct fw_xfer*) ; 

__attribute__((used)) static void
sbp_recv(struct fw_xfer *xfer)
{
	struct sbp_softc *sbp;

	sbp = (struct sbp_softc *)xfer->sc;
	SBP_LOCK(sbp);
	sbp_recv1(xfer);
	SBP_UNLOCK(sbp);
}