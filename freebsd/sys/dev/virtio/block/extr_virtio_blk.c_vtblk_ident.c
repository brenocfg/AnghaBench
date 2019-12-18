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
struct vtblk_softc {int /*<<< orphan*/  vtblk_dev; struct disk* vtblk_disk; } ;
struct TYPE_2__ {int ioprio; scalar_t__ sector; int /*<<< orphan*/  type; } ;
struct vtblk_request {int vbr_ack; struct bio* vbr_bp; TYPE_1__ vbr_hdr; } ;
struct disk {int /*<<< orphan*/  d_ident; } ;
struct bio {int bio_bcount; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  DISK_IDENT_SIZE ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_BLK_ID_BYTES ; 
 int /*<<< orphan*/  VIRTIO_BLK_T_GET_ID ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 
 int /*<<< orphan*/  vtblk_no_ident ; 
 int vtblk_poll_request (struct vtblk_softc*,struct vtblk_request*) ; 
 struct vtblk_request* vtblk_request_dequeue (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_request_enqueue (struct vtblk_softc*,struct vtblk_request*) ; 
 scalar_t__ vtblk_tunable_int (struct vtblk_softc*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtblk_ident(struct vtblk_softc *sc)
{
	struct bio buf;
	struct disk *dp;
	struct vtblk_request *req;
	int len, error;

	dp = sc->vtblk_disk;
	len = MIN(VIRTIO_BLK_ID_BYTES, DISK_IDENT_SIZE);

	if (vtblk_tunable_int(sc, "no_ident", vtblk_no_ident) != 0)
		return;

	req = vtblk_request_dequeue(sc);
	if (req == NULL)
		return;

	req->vbr_ack = -1;
	req->vbr_hdr.type = VIRTIO_BLK_T_GET_ID;
	req->vbr_hdr.ioprio = 1;
	req->vbr_hdr.sector = 0;

	req->vbr_bp = &buf;
	g_reset_bio(&buf);

	buf.bio_cmd = BIO_READ;
	buf.bio_data = dp->d_ident;
	buf.bio_bcount = len;

	VTBLK_LOCK(sc);
	error = vtblk_poll_request(sc, req);
	VTBLK_UNLOCK(sc);

	vtblk_request_enqueue(sc, req);

	if (error) {
		device_printf(sc->vtblk_dev,
		    "error getting device identifier: %d\n", error);
	}
}