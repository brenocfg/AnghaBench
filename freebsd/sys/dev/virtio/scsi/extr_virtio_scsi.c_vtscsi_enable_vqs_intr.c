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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_request_vq; int /*<<< orphan*/  vtscsi_event_vq; int /*<<< orphan*/  vtscsi_control_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_enable_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_enable_vqs_intr(struct vtscsi_softc *sc)
{

	virtqueue_enable_intr(sc->vtscsi_control_vq);
	virtqueue_enable_intr(sc->vtscsi_event_vq);
	virtqueue_enable_intr(sc->vtscsi_request_vq);
}