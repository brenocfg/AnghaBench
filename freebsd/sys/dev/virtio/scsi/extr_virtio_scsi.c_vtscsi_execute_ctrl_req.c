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
struct vtscsi_softc {struct virtqueue* vtscsi_control_vq; } ;
struct vtscsi_request {int /*<<< orphan*/ * vsr_complete; } ;
struct virtqueue {int dummy; } ;
struct sglist {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EMSGSIZE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int VTSCSI_EXECUTE_POLL ; 
 int virtqueue_enqueue (struct virtqueue*,struct vtscsi_request*,struct sglist*,int,int) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 
 int /*<<< orphan*/  vtscsi_poll_ctrl_req (struct vtscsi_softc*,struct vtscsi_request*) ; 

__attribute__((used)) static int
vtscsi_execute_ctrl_req(struct vtscsi_softc *sc, struct vtscsi_request *req,
    struct sglist *sg, int readable, int writable, int flag)
{
	struct virtqueue *vq;
	int error;

	vq = sc->vtscsi_control_vq;

	MPASS(flag == VTSCSI_EXECUTE_POLL || req->vsr_complete != NULL);

	error = virtqueue_enqueue(vq, req, sg, readable, writable);
	if (error) {
		/*
		 * Return EAGAIN when the virtqueue does not have enough
		 * descriptors available.
		 */
		if (error == ENOSPC || error == EMSGSIZE)
			error = EAGAIN;

		return (error);
	}

	virtqueue_notify(vq);
	if (flag == VTSCSI_EXECUTE_POLL)
		vtscsi_poll_ctrl_req(sc, req);

	return (0);
}