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
struct vtscsi_softc {struct virtqueue* vtscsi_event_vq; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * virtqueue_drain (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  virtqueue_empty (struct virtqueue*) ; 

__attribute__((used)) static void
vtscsi_drain_event_vq(struct vtscsi_softc *sc)
{
	struct virtqueue *vq;
	int last;

	vq = sc->vtscsi_event_vq;
	last = 0;

	while (virtqueue_drain(vq, &last) != NULL)
		;

	KASSERT(virtqueue_empty(vq), ("eventvq not empty"));
}