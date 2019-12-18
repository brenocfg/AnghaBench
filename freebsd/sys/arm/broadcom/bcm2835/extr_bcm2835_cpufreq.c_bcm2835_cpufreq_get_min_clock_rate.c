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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {scalar_t__ rate_hz; } ;
struct TYPE_8__ {int /*<<< orphan*/  clock_id; } ;
struct TYPE_10__ {TYPE_4__ resp; TYPE_3__ req; } ;
struct TYPE_7__ {int val_buf_size; int val_len; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int buf_size; int /*<<< orphan*/  code; } ;
struct msg_get_min_clock_rate {TYPE_5__ body; scalar_t__ end_tag; TYPE_2__ tag_hdr; TYPE_1__ hdr; } ;
struct bcm2835_cpufreq_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CODE_REQ ; 
 int /*<<< orphan*/  BCM2835_MBOX_TAG_GET_MIN_CLOCK_RATE ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int MSG_ERROR ; 
 int bcm2835_mbox_property (struct msg_get_min_clock_rate*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct msg_get_min_clock_rate*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bcm2835_cpufreq_get_min_clock_rate(struct bcm2835_cpufreq_softc *sc,
    uint32_t clock_id)
{
	struct msg_get_min_clock_rate msg;
	int rate;
	int err;

	/*
	 * Get min clock rate
	 *   Tag: 0x00030007
	 *   Request:
	 *     Length: 4
	 *     Value:
	 *       u32: clock id
	 *   Response:
	 *     Length: 8
	 *     Value:
	 *       u32: clock id
	 *       u32: rate (in Hz)
	 */

	/* setup single tag buffer */
	memset(&msg, 0, sizeof(msg));
	msg.hdr.buf_size = sizeof(msg);
	msg.hdr.code = BCM2835_MBOX_CODE_REQ;
	msg.tag_hdr.tag = BCM2835_MBOX_TAG_GET_MIN_CLOCK_RATE;
	msg.tag_hdr.val_buf_size = sizeof(msg.body);
	msg.tag_hdr.val_len = sizeof(msg.body.req);
	msg.body.req.clock_id = clock_id;
	msg.end_tag = 0;

	/* call mailbox property */
	err = bcm2835_mbox_property(&msg, sizeof(msg));
	if (err) {
		device_printf(sc->dev, "can't get min clock rate (id=%u)\n",
		    clock_id);
		return (MSG_ERROR);
	}

	/* result (Hz) */
	rate = (int)msg.body.resp.rate_hz;
	DPRINTF("clock = %d(Hz)\n", rate);
	return (rate);
}