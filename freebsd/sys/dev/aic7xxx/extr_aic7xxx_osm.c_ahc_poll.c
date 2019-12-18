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
struct cam_sim {int dummy; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_intr (struct ahc_softc*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 

__attribute__((used)) static void
ahc_poll(struct cam_sim *sim)
{
	struct ahc_softc *ahc;

	ahc = (struct ahc_softc *)cam_sim_softc(sim);
	ahc_intr(ahc);
}