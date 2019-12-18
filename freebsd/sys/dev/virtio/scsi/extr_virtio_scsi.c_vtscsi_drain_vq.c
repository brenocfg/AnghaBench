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
struct vtscsi_request {int dummy; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 struct vtscsi_request* virtqueue_drain (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  virtqueue_empty (struct virtqueue*) ; 
 int /*<<< orphan*/  vtscsi_cancel_request (struct vtscsi_softc*,struct vtscsi_request*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct virtqueue*) ; 

__attribute__((used)) static void
vtscsi_drain_vq(struct vtscsi_softc *sc, struct virtqueue *vq)
{
	struct vtscsi_request *req;
	int last;

	last = 0;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "vq=%p\n", vq);

	while ((req = virtqueue_drain(vq, &last)) != NULL)
		vtscsi_cancel_request(sc, req);

	KASSERT(virtqueue_empty(vq), ("virtqueue not empty"));
}