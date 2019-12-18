#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int pay_len; } ;
struct TYPE_6__ {int dst; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
struct TYPE_8__ {TYPE_2__ mode; } ;
struct TYPE_9__ {int pay_len; int /*<<< orphan*/  spd; TYPE_3__ hdr; } ;
struct fw_xfer {TYPE_5__ recv; TYPE_4__ send; int /*<<< orphan*/  sc; void* hand; int /*<<< orphan*/  fc; } ;
struct fw_device {int dst; int /*<<< orphan*/  speed; int /*<<< orphan*/  fc; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int FWLOCALBUS ; 
 int /*<<< orphan*/  M_FWMEM ; 
 struct fw_xfer* fw_xfer_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fw_xfer *
fwmem_xfer_req(
	struct fw_device *fwdev,
	caddr_t sc,
	int spd,
	int slen,
	int rlen,
	void *hand)
{
	struct fw_xfer *xfer;

	xfer = fw_xfer_alloc(M_FWMEM);
	if (xfer == NULL)
		return NULL;

	xfer->fc = fwdev->fc;
	xfer->send.hdr.mode.hdr.dst = FWLOCALBUS | fwdev->dst;
	if (spd < 0)
		xfer->send.spd = fwdev->speed;
	else
		xfer->send.spd = min(spd, fwdev->speed);
	xfer->hand = hand;
	xfer->sc = sc;
	xfer->send.pay_len = slen;
	xfer->recv.pay_len = rlen;

	return xfer;
}