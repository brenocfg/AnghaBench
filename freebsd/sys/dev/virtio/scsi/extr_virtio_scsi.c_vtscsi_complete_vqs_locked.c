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
struct vtscsi_softc {int /*<<< orphan*/ * vtscsi_control_vq; int /*<<< orphan*/ * vtscsi_request_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_LOCK_OWNED (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_complete_vq (struct vtscsi_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtscsi_complete_vqs_locked(struct vtscsi_softc *sc)
{

	VTSCSI_LOCK_OWNED(sc);

	if (sc->vtscsi_request_vq != NULL)
		vtscsi_complete_vq(sc, sc->vtscsi_request_vq);
	if (sc->vtscsi_control_vq != NULL)
		vtscsi_complete_vq(sc, sc->vtscsi_control_vq);
}