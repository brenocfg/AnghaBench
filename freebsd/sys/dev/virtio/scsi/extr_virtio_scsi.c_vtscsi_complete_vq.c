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
 int /*<<< orphan*/  VTSCSI_LOCK_OWNED (struct vtscsi_softc*) ; 
 struct vtscsi_request* virtqueue_dequeue (struct virtqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtscsi_complete_request (struct vtscsi_request*) ; 

__attribute__((used)) static void
vtscsi_complete_vq(struct vtscsi_softc *sc, struct virtqueue *vq)
{
	struct vtscsi_request *req;

	VTSCSI_LOCK_OWNED(sc);

	while ((req = virtqueue_dequeue(vq, NULL)) != NULL)
		vtscsi_complete_request(req);
}