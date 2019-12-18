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
struct mpt_softc {int dummy; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  mpt_intr (struct mpt_softc*) ; 

__attribute__((used)) static void
mpt_poll(struct cam_sim *sim)
{
	struct mpt_softc *mpt;

	mpt = (struct mpt_softc *)cam_sim_softc(sim);
	mpt_intr(mpt);
}