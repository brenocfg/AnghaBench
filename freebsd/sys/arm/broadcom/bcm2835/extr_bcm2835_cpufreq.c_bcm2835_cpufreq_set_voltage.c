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
typedef  void* uint32_t ;
struct TYPE_9__ {scalar_t__ value; } ;
struct TYPE_8__ {void* value; void* voltage_id; } ;
struct TYPE_10__ {TYPE_4__ resp; TYPE_3__ req; } ;
struct TYPE_7__ {int val_buf_size; int val_len; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int buf_size; int /*<<< orphan*/  code; } ;
struct msg_set_voltage {TYPE_5__ body; scalar_t__ end_tag; TYPE_2__ tag_hdr; TYPE_1__ hdr; } ;
struct bcm2835_cpufreq_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CODE_REQ ; 
 int /*<<< orphan*/  BCM2835_MBOX_TAG_SET_VOLTAGE ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int MAX_OVER_VOLTAGE ; 
 int MIN_OVER_VOLTAGE ; 
 int MSG_ERROR ; 
 int bcm2835_mbox_property (struct msg_set_voltage*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct msg_set_voltage*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bcm2835_cpufreq_set_voltage(struct bcm2835_cpufreq_softc *sc,
    uint32_t voltage_id, int32_t value)
{
	struct msg_set_voltage msg;
	int err;

	/*
	 * Set voltage
	 *   Tag: 0x00038003
	 *   Request:
	 *     Length: 4
	 *     Value:
	 *       u32: voltage id
	 *       u32: value (offset from 1.2V in units of 0.025V)
	 *   Response:
	 *     Length: 8
	 *     Value:
	 *       u32: voltage id
	 *       u32: value (offset from 1.2V in units of 0.025V)
	 */

	/*
	 * over_voltage:
	 * 0 (1.2 V). Values above 6 are only allowed when force_turbo or
	 * current_limit_override are specified (which set the warranty bit).
	 */
	if (value > MAX_OVER_VOLTAGE || value < MIN_OVER_VOLTAGE) {
		/* currently not supported */
		device_printf(sc->dev, "not supported voltage: %d\n", value);
		return (MSG_ERROR);
	}

	/* setup single tag buffer */
	memset(&msg, 0, sizeof(msg));
	msg.hdr.buf_size = sizeof(msg);
	msg.hdr.code = BCM2835_MBOX_CODE_REQ;
	msg.tag_hdr.tag = BCM2835_MBOX_TAG_SET_VOLTAGE;
	msg.tag_hdr.val_buf_size = sizeof(msg.body);
	msg.tag_hdr.val_len = sizeof(msg.body.req);
	msg.body.req.voltage_id = voltage_id;
	msg.body.req.value = (uint32_t)value;
	msg.end_tag = 0;

	/* call mailbox property */
	err = bcm2835_mbox_property(&msg, sizeof(msg));
	if (err) {
		device_printf(sc->dev, "can't set voltage\n");
		return (MSG_ERROR);
	}

	/* result (offset from 1.2V) */
	value = (int)msg.body.resp.value;
	DPRINTF("value = %d\n", value);
	return (value);
}