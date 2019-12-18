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
struct targ_softc {int /*<<< orphan*/  path; struct cam_periph* periph; } ;
struct cam_periph {int /*<<< orphan*/  path; struct targ_softc* softc; } ;
typedef  int /*<<< orphan*/  cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 

__attribute__((used)) static cam_status
targctor(struct cam_periph *periph, void *arg)
{
	struct targ_softc *softc;

	/* Store pointer to softc for periph-driven routines */
	softc = (struct targ_softc *)arg;
	periph->softc = softc;
	softc->periph = periph;
	softc->path = periph->path;
	return (CAM_REQ_CMP);
}