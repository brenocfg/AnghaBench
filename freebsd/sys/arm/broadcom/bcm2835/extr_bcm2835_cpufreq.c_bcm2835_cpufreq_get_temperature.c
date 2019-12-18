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
struct TYPE_9__ {scalar_t__ value; } ;
struct TYPE_8__ {scalar_t__ temperature_id; } ;
struct TYPE_10__ {TYPE_4__ resp; TYPE_3__ req; } ;
struct TYPE_7__ {int val_buf_size; int val_len; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int buf_size; int /*<<< orphan*/  code; } ;
struct msg_get_temperature {TYPE_5__ body; scalar_t__ end_tag; TYPE_2__ tag_hdr; TYPE_1__ hdr; } ;
struct bcm2835_cpufreq_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CODE_REQ ; 
 int /*<<< orphan*/  BCM2835_MBOX_TAG_GET_TEMPERATURE ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int MSG_ERROR ; 
 int bcm2835_mbox_property (struct msg_get_temperature*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct msg_get_temperature*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bcm2835_cpufreq_get_temperature(struct bcm2835_cpufreq_softc *sc)
{
	struct msg_get_temperature msg;
	int value;
	int err;

	/*
	 * Get temperature
	 *   Tag: 0x00030006
	 *   Request:
	 *     Length: 4
	 *     Value:
	 *       u32: temperature id
	 *   Response:
	 *     Length: 8
	 *     Value:
	 *       u32: temperature id
	 *       u32: value
	 */

	/* setup single tag buffer */
	memset(&msg, 0, sizeof(msg));
	msg.hdr.buf_size = sizeof(msg);
	msg.hdr.code = BCM2835_MBOX_CODE_REQ;
	msg.tag_hdr.tag = BCM2835_MBOX_TAG_GET_TEMPERATURE;
	msg.tag_hdr.val_buf_size = sizeof(msg.body);
	msg.tag_hdr.val_len = sizeof(msg.body.req);
	msg.body.req.temperature_id = 0;
	msg.end_tag = 0;

	/* call mailbox property */
	err = bcm2835_mbox_property(&msg, sizeof(msg));
	if (err) {
		device_printf(sc->dev, "can't get temperature\n");
		return (MSG_ERROR);
	}

	/* result (temperature of degree C) */
	value = (int)msg.body.resp.value;
	DPRINTF("value = %d\n", value);
	return (value);
}