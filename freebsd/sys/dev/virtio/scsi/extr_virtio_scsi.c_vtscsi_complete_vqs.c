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
struct vtscsi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_complete_vqs_locked (struct vtscsi_softc*) ; 

__attribute__((used)) static void
vtscsi_complete_vqs(struct vtscsi_softc *sc)
{

	VTSCSI_LOCK(sc);
	vtscsi_complete_vqs_locked(sc);
	VTSCSI_UNLOCK(sc);
}