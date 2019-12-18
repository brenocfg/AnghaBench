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
struct vtscsi_softc {int vtscsi_event_buf_size; struct virtqueue* vtscsi_event_vq; struct sglist* vtscsi_sglist; } ;
struct virtqueue {int dummy; } ;
struct virtio_scsi_event {int dummy; } ;
struct sglist {int /*<<< orphan*/  sg_nseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct virtio_scsi_event*,int) ; 
 int sglist_append (struct sglist*,struct virtio_scsi_event*,int) ; 
 int /*<<< orphan*/  sglist_reset (struct sglist*) ; 
 int virtqueue_enqueue (struct virtqueue*,struct virtio_scsi_event*,struct sglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 

__attribute__((used)) static int
vtscsi_enqueue_event_buf(struct vtscsi_softc *sc,
    struct virtio_scsi_event *event)
{
	struct sglist *sg;
	struct virtqueue *vq;
	int size, error;

	sg = sc->vtscsi_sglist;
	vq = sc->vtscsi_event_vq;
	size = sc->vtscsi_event_buf_size;

	bzero(event, size);

	sglist_reset(sg);
	error = sglist_append(sg, event, size);
	if (error)
		return (error);

	error = virtqueue_enqueue(vq, event, sg, 0, sg->sg_nseg);
	if (error)
		return (error);

	virtqueue_notify(vq);

	return (0);
}