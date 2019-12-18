#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ioprio; int sector; int /*<<< orphan*/  type; } ;
struct vtblk_request {int vbr_ack; struct bio* vbr_bp; TYPE_1__ vbr_hdr; } ;
struct vtblk_softc {struct vtblk_request vtblk_dump_request; } ;
struct bio {size_t bio_bcount; void* bio_data; int /*<<< orphan*/  bio_cmd; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  VIRTIO_BLK_T_OUT ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 
 int vtblk_poll_request (struct vtblk_softc*,struct vtblk_request*) ; 

__attribute__((used)) static int
vtblk_dump_write(struct vtblk_softc *sc, void *virtual, off_t offset,
    size_t length)
{
	struct bio buf;
	struct vtblk_request *req;

	req = &sc->vtblk_dump_request;
	req->vbr_ack = -1;
	req->vbr_hdr.type = VIRTIO_BLK_T_OUT;
	req->vbr_hdr.ioprio = 1;
	req->vbr_hdr.sector = offset / 512;

	req->vbr_bp = &buf;
	g_reset_bio(&buf);

	buf.bio_cmd = BIO_WRITE;
	buf.bio_data = virtual;
	buf.bio_bcount = length;

	return (vtblk_poll_request(sc, req));
}