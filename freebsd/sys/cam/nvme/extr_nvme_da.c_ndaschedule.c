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
struct nda_softc {scalar_t__ state; int /*<<< orphan*/  cam_iosched; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 scalar_t__ NDA_STATE_NORMAL ; 
 int /*<<< orphan*/  cam_iosched_schedule (int /*<<< orphan*/ ,struct cam_periph*) ; 

__attribute__((used)) static void
ndaschedule(struct cam_periph *periph)
{
	struct nda_softc *softc = (struct nda_softc *)periph->softc;

	if (softc->state != NDA_STATE_NORMAL)
		return;

	cam_iosched_schedule(softc->cam_iosched, periph);
}