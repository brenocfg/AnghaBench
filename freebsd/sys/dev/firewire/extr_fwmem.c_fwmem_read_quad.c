#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int* payload; } ;
struct TYPE_5__ {int dest_hi; int dest_lo; int /*<<< orphan*/  tcode; } ;
struct TYPE_6__ {TYPE_1__ rreqq; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct TYPE_7__ {int /*<<< orphan*/ * payload; struct fw_pkt hdr; } ;
struct fw_xfer {int /*<<< orphan*/  fc; TYPE_4__ recv; TYPE_3__ send; } ;
struct fw_device {int dst; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWTCODE_RREQQ ; 
 scalar_t__ fw_asyreq (int /*<<< orphan*/ ,int,struct fw_xfer*) ; 
 int /*<<< orphan*/  fw_xfer_free (struct fw_xfer*) ; 
 scalar_t__ fwmem_debug ; 
 struct fw_xfer* fwmem_xfer_req (struct fw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void (*) (struct fw_xfer*)) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

struct fw_xfer *
fwmem_read_quad(
	struct fw_device *fwdev,
	caddr_t	sc,
	uint8_t spd,
	uint16_t dst_hi,
	uint32_t dst_lo,
	void *data,
	void (*hand)(struct fw_xfer *))
{
	struct fw_xfer *xfer;
	struct fw_pkt *fp;

	xfer = fwmem_xfer_req(fwdev, sc, spd, 0, 4, hand);
	if (xfer == NULL) {
		return NULL;
	}

	fp = &xfer->send.hdr;
	fp->mode.rreqq.tcode = FWTCODE_RREQQ;
	fp->mode.rreqq.dest_hi = dst_hi;
	fp->mode.rreqq.dest_lo = dst_lo;

	xfer->send.payload = NULL;
	xfer->recv.payload = (uint32_t *)data;

	if (fwmem_debug)
		printf("fwmem_read_quad: %d %04x:%08x\n", fwdev->dst,
		    dst_hi, dst_lo);

	if (fw_asyreq(xfer->fc, -1, xfer) == 0)
		return xfer;

	fw_xfer_free(xfer);
	return NULL;
}